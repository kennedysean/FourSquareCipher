#include<iostream>
using std::cout; using std::cin; using std::endl;
#include<string>
using std::string; using std::to_string;
#include<fstream>
using std::ifstream; using std::ofstream;
#include<sstream>
using std::ostringstream;

/*
Four-Square Cipher for Text File Encryption/Decryption
*/

string clean_string(string s) {
	string return_string = "";

	//return a lowercase version of the input string with only letters, ignoring 'q'
	for (long i = 0; i < s.size(); i++) {
		char character = s[i];
		if (isalpha(character) && character != 'q')
			return_string += tolower(character);
	}
	return return_string;
}


string create_encoding(string key) {
	//block encoding does not include 'q'
	string keyword_encoding = "abcdefghijklmnoprstuvwxyz";

	//create and return an encoded block for the keyword
	for (long i = key.size() - 1; i >= 0; i -= 1) {
		if (key[i] != 'q') {
			auto index = keyword_encoding.find(key[i]);
			keyword_encoding.erase(index, 1);
			keyword_encoding = key[i] + keyword_encoding;
		}
	}
	return keyword_encoding;
}

//encode a two letter string (digraph) using keyword blocks
string encode_digraph(string dg, string block1, string block2) {
	string encoded_digraph = "";
	string alphabet_block = "abcdefghijklmnoprstuvwxyz";
	char first_letter = dg[0];
	char second_letter = dg[1];
	int first_index = alphabet_block.find(first_letter);
	int second_index = alphabet_block.find(second_letter);
	int first_row = first_index / 5;
	int first_column = first_index % 5;
	int second_row = second_index / 5;
	int second_column = second_index % 5;

	//find index in encoded blocks
	int first_encoded_index = 5 * first_row + second_column;
	int second_encoded_index = 5 * second_row + first_column;

	//find encoded letters in blocks
	char first_encoded_letter = block1[first_encoded_index];
	char second_encoded_letter = block2[second_encoded_index];

	//create encoded digraph
	encoded_digraph = encoded_digraph + first_encoded_letter;
	encoded_digraph = encoded_digraph + second_encoded_letter;
	return encoded_digraph;
}

//decode an encoded two letter string (digraph) using keyword blocks
string decode_digraph(string dg, string block1, string block2) {
	string decoded_digraph = "";
	string alphabet_block = "abcdefghijklmnoprstuvwxyz";
	char first_letter = dg[0];
	char second_letter = dg[1];
	int first_index = block1.find(first_letter);
	int second_index = block2.find(second_letter);
	int first_row = first_index / 5;
	int first_column = first_index % 5;
	int second_row = second_index / 5;
	int second_column = second_index % 5;

	//find index in alphabet blocks
	int first_decoded_index = 5 * first_row + second_column;
	int second_decoded_index = 5 * second_row + first_column;

	//find decoded letters in alphabet blocks
	char first_decoded_letter = alphabet_block[first_decoded_index];
	char second_decoded_letter = alphabet_block[second_decoded_index];

	//create decoded digraph
	decoded_digraph = decoded_digraph + first_decoded_letter;
	decoded_digraph = decoded_digraph + second_decoded_letter;
	return decoded_digraph;
}

//encode a message using keyword blocks
string encode(string msg, string key1, string key2) {
	string encoded_message = "";
	string block1 = create_encoding(key1);
	string block2 = create_encoding(key2);
	string message = clean_string(msg);
	long message_length = message.size();

	//add "x" to end of message if string has an odd number of letters
	if (message_length % 2 == 1)
		message += "x";

	//string together the encoded digraphs to make the encoded message
	for (long i = 0; i < message_length; i += 2) {
		string digraph = message.substr(i, 2);
		string encoded_digraph = encode_digraph(digraph, block1, block2);
		encoded_message += encoded_digraph;
	}
	return encoded_message;
}

//decode an encoded message using keyword blocks
string decode(string msg, string key1, string key2) {
	string decoded_message = "";
	string block1 = create_encoding(key1);
	string block2 = create_encoding(key2);
	string message = clean_string(msg);
	long message_length = message.size();

	//string together decoded digraphs to make decoded message
	for (long i = 0; i < message_length; i += 2) {
		string digraph = message.substr(i, 2);
		string decoded_digraph = decode_digraph(digraph, block1, block2);
		decoded_message += decoded_digraph;
	}
	return decoded_message;
}

int main() {
	string message;
	string keyword1;
	string keyword2;
	string answer;
	cout << "If you want to encrypt a message from a text file, please input 1.\n";
	cout << "If you want to decrypt a message from a text file, please input 2.";
	cout << "\nInput: ";
	cin >> answer;
	while (answer != "1" && answer != "2") {
		cout << "Invalid input. Please input '1' (encrypt) or '2' (decrypt).\n";
		cout << "Input: ";
		cin >> answer;
	}
	cout << "Enter Keyword 1 (lowercase): ";
	cin >> keyword1;
	cout << "Enter Keyword 2 (lowercase): ";
	cin >> keyword2;
	if (answer == "1") {
		answer = "";
		cout << "Enter name of text file to be encoded: ";
		cin >> answer;
		ifstream file(answer);
		if (! file)
			cout << "File does not exist in working directory (program terminated).";
		else {
			string message;
			ostringstream oss;
			while (file >> message) {
				oss << message;
			}
			message=oss.str();
			string encoded_message = encode(message, keyword1, keyword2);
			ofstream new_file;
			new_file.open("encryption.txt");
			new_file << encoded_message;
			new_file.close();
		}
	}
	else if (answer == "2") {
		answer = "";
		cout << "Enter name of text file to be decoded: ";
		cin >> answer;
		ifstream file(answer);
		if (! file)
			cout << "File does not exist in working directory (program terminated).";
		else {
			string message;
			ostringstream oss;
			while (file >> message) {
				oss << message;
			}
			message=oss.str();
			string decoded_message = decode(message, keyword1, keyword2);
			ofstream new_file;
			new_file.open("decryption.txt");
			new_file << decoded_message;
			new_file.close();
		}
	}
}