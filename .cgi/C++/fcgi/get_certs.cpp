void get_certs (Process& proc)
{
	cout << "<head><TITLE>Certificates</TITLE>\n";
	fstream fin ("./help_files/removeParams.js");
	string b;
	getline (fin, b);
	cout << b << "\n</head>";
	string user = proc.query_string ["username"];

	cout << "<h1>" << user << "</h1>";
	for (auto& y : user_certs [user])
	{
		cout << "<a href='/.cgi?type=verify_cert&id=" + y.second.id + "'><h2>" + y.second.course + "</h2></a><br>";
	}
}
