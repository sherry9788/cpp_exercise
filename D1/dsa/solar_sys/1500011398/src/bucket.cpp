#include "bucket.h"

bucket::bucket() {
	std::fstream file_out("bucket.bat", fstream::out);
	file_out << "@echo off\n";
	file_out << "md %1\n";
	file_out << "cd %1\n";
	file_out << "md %2\n";
	file_out << "cd %2\n";
	file_out << "md %3\n";
	file_out << "cd %3" << endl;
}

void bucket::enter(const int &index_1, const int &index_2, const int &index_3,
	const double &value_1, const double &value_2, const double &value_3) {

	std::string string_1, string_2, string_3;
	std::strstream ss;

	ss << index_1;
	ss >> string_1;
	ss.clear();

	ss << index_2;
	ss >> string_2;
	ss.clear();

	ss << index_3;
	ss >> string_3;
	ss.clear();

	std::string cmd = "bucket.bat ";
	cmd = cmd + string_1 + " " + string_2 + " " + string_3;
	system(&cmd[0]);
	std::string file_path = "";
	file_path += string_1 + '\\';
	file_path += string_2 + '\\';
	file_path += string_3 + '\\';
	file_path += "info.dat";
	fstream file_out(file_path, fstream::app);
	file_out << value_1 << " " << value_2 << " " << value_3;
}
#include <iostream>

void bucket::get_data(const int &index_1, const int &index_2, const int &index_3,
	double &value_1, double &value_2, double &value_3) {

	std::string string_1, string_2, string_3;
	std::strstream ss;

	ss << index_1;
	ss >> string_1;
	ss.clear();

	ss << index_2;
	ss >> string_2;
	ss.clear();

	ss << index_3;
	ss >> string_3;
	ss.clear();

	std::string file_path = ".\\";
	file_path += string_1 + '\\';
	file_path += string_2 + '\\';
	file_path += string_3 + '\\';
	file_path += "info.dat";
	
	fstream file_in(file_path, fstream::in);
	
	
	file_in >> value_1 >> value_2 >> value_3;
}
