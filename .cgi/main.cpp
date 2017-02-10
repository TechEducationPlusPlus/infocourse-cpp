#include <exception>

using namespace std;

#include <C++/fcgi/params.hpp>
#include <C++/fcgi/base.hpp>

void Throw (string a)
{
	cout << a << "\n";
}

Process proc;
map <string, map <string, map <string, int> > > user_points;

#include <C++/fcgi/contest.hpp>
#include <C++/fcgi/cert.hpp>
#include <C++/fcgi/register.hpp>
#include <C++/fcgi/user.hpp>

map <string, map <string, certify > > user_certs;
#include <C++/fcgi/verify.hpp>
#include <C++/fcgi/get_certs.cpp>

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

//        cout << "Set-coockie: name-value\r\n\r\n";
		//cout <<
        //        "<H1>echo-cpp</H1>\n"
        //        "<H4>PID: " << pid << "</H4>\n"
        //        "<H4>Request Number: " << ++count << "</H4>\n";

        //cout << "<H4>Request Environment</H4>\n";
        proc.set_args (request.envp);
		{
			cout << "Content-type: text/html\r\n";
			if (proc.params ["QUERY_STRING"] == "")
				Throw (HTML::invalid_page);
			else
			{
				cout << HTML::viewport << "\n";
				if (proc.query_string ["type"] == "cert")
				{
					try
					{
						cert (proc);
					}
					catch (exception& e)
					{
						Throw (e.what ());
					}
				}
				else if (proc.query_string ["type"] == "register")
				{
					try
					{
						register_user (proc);
					}
					catch (exception& e)
					{
						Throw (e.what ());
					}
				}
				else if (proc.query_string ["type"] == "get_contest")
				{
					try
					{
						contest (proc);
					}
					catch (exception& e)
					{
						Throw (e.what ());
					}
				}
				else if (proc.query_string ["type"] == "user")
				{
					try
					{
						user (proc);
					}
					catch (exception& e)
					{
						Throw (e.what ());
					}
				}
				else if (proc.query_string ["type"] == "verify_cert")
				{
					try
					{
						verify_certificate (proc);
					}
					catch (exception& e)
					{
						Throw (e.what ());
					}
				}
				else if (proc.query_string ["type"] == "get_certs")
				{
					try
					{
						get_certs (proc);
					}
					catch (exception& e)
					{
						Throw (e.what ());
					}
				}
				else if (proc.query_string ["type"] == "new_cert")
				{
					try
					{
						new_certificate (proc);
					}
					catch (exception& e)
					{
						Throw (e.what ());
					}
				}
				else
					Throw (HTML::invalid_type);
			}
		}
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
				//cout << "<H4>Process/Initial Environment</H4>\n";
				//penv(environ);

				//cout << "<H4>Standard Input - " << clen;
				//if (clen == STDIN_MAX) cout << " (STDIN_MAX)";
				//cout << " bytes</H4>\n";
				//if (clen) cout.write(content, clen);

				//cout << "<H1>Form prameters: " << params ["QUERY_STRING"] << "</H1>";
				//cout << "<H2>First Name: " << splitQueryString (params ["QUERY_STRING"])["first_name"] << "</H1>";

				//cout << "<H1>Form prameters: " << params ["QUERY_STRING"] << "</H1>";
				//cout << "<H2>First Name: " << splitQueryString (params ["QUERY_STRING"])["first_name"] << "</H1>";
