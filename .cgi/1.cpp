#include <stdlib.h>
#ifdef _WIN32
#include <process.h>
#else
#include <unistd.h>
extern char ** environ;
#endif
#include "fcgio.h"
#include "fcgi_config.h"

using namespace std;

static const unsigned long STDIN_MAX = 1000000;

static void penv(const char * const * envp)
{
    cout << "<PRE>\n";
    for ( ; *envp; ++envp)
    {
        cout << *envp << "\n";
    }
    cout << "</PRE>\n";
}

static long gstdin(FCGX_Request * request, char ** content)
{
    char * clenstr = FCGX_GetParam("CONTENT_LENGTH", request->envp);
    unsigned long clen = STDIN_MAX;

    if (clenstr)
    {
        clen = strtol(clenstr, &clenstr, 10);
        if (*clenstr)
        {
            cerr << "can't parse \"CONTENT_LENGTH="
                 << FCGX_GetParam("CONTENT_LENGTH", request->envp)
                 << "\"\n";
            clen = STDIN_MAX;
        }

        // *always* put a cap on the amount of data that will be read
        if (clen > STDIN_MAX) clen = STDIN_MAX;

        *content = new char[clen];

        cin.read(*content, clen);
        clen = cin.gcount();
    }
    else
    {
        // *never* read stdin when CONTENT_LENGTH is missing or unparsable
        *content = 0;
        clen = 0;
    }

    // Chew up any remaining stdin - this shouldn't be necessary
    // but is because mod_fastcgi doesn't handle it correctly.

    // ignore() doesn't set the eof bit in some versions of glibc++
    // so use gcount() instead of eof()...
    do 
		cin.ignore(1024); 
	while (cin.gcount() == 1024);

    return clen;
}

#include <map>
#include <string>

map <string, string> params;

map <string, string> splitQueryString (string a)
{
	map <string, string> ans;
	string param [2];
	int ind = 0;
	for (int i = 0 ; i < a.size () ; i ++)
	{
		if (a [i] == '&')
		{
			ans [param [0]] = param [1];
			param [0] = param [1] = "";
			ind = 0;
		}
		else if (a [i] == '=')
		{
			ind ++;
		}
		else
			param [ind] += a [i];
	}
	return move (ans);
}

void make_params (const char * const * envp)
{
    for ( ; *envp; ++envp)
    {
		int ind = 0;
		string index = "", value = "";
		for ( ; (*envp)[ind] != '=' ; ind ++)
			index += (*envp)[ind];

		for (ind ++ ; (*envp)[ind] != '\0' ; ind ++)
			value += (*envp)[ind];

		params [index] = value;
    }
}


int main ()
{
    int count = 0;
    long pid = getpid();

    streambuf * cin_streambuf  = cin.rdbuf ();
    streambuf * cout_streambuf = cout.rdbuf ();
    streambuf * cerr_streambuf = cerr.rdbuf ();

    FCGX_Request request;

    FCGX_Init ();
    FCGX_InitRequest (&request, 0, 0);

    while (FCGX_Accept_r (&request) == 0)
    {
        fcgi_streambuf cin_fcgi_streambuf (request.in);
        fcgi_streambuf cout_fcgi_streambuf (request.out);
        fcgi_streambuf cerr_fcgi_streambuf (request.err);

#if HAVE_IOSTREAM_WITHASSIGN_STREAMBUF
        cin  = &cin_fcgi_streambuf;
        cout = &cout_fcgi_streambuf;
        cerr = &cerr_fcgi_streambuf;
#else
        cin.rdbuf (&cin_fcgi_streambuf);
        cout.rdbuf (&cout_fcgi_streambuf);
        cerr.rdbuf (&cerr_fcgi_streambuf);
#endif

        char * content;
        unsigned long clen = gstdin(&request, &content);

        cout << "Content-type: text/html\r\n"
                "\r\n"
                "<TITLE>echo-cpp</TITLE>\n"
                "<H1>echo-cpp</H1>\n"
                "<H4>PID: " << pid << "</H4>\n"
                "<H4>Request Number: " << ++count << "</H4>\n";

        cout << "<H4>Request Environment</H4>\n";
        make_params (request.envp);
        penv(request.envp);

        cout << "<H4>Process/Initial Environment</H4>\n";
        penv(environ);

        cout << "<H4>Standard Input - " << clen;
        if (clen == STDIN_MAX) cout << " (STDIN_MAX)";
        cout << " bytes</H4>\n";
        if (clen) cout.write(content, clen);

		cout << "<H1>Form prameters: " << params ["QUERY_STRING"] << "</H1>";
		cout << "<H2>First Name: " << splitQueryString (params ["QUERY_STRING"])["first_name"] << "</H1>";

        if (content) delete []content;
    }

#if HAVE_IOSTREAM_WITHASSIGN_STREAMBUF
    cin  = cin_streambuf;
    cout = cout_streambuf;
    cerr = cerr_streambuf;
#else
    cin.rdbuf(cin_streambuf);
    cout.rdbuf(cout_streambuf);
    cerr.rdbuf(cerr_streambuf);
#endif

    return 0;
}
