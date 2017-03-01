#include <vector>
#include <string>
#include <iostream>
#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Value_Input.H>

using namespace std;

class Patron {
  private:
    string name;
    string phone;
  public:
    Patron(string _name, string _phone);
    string to_string();
    string getName();
    string getPhone();
};

Patron::Patron(string _name, string _phone) {
  name = _name;
  phone = _phone;
}

string Patron::getName() {
	return name;
}

string Patron::getPhone() {
	return phone;
}

string Patron::to_string() {

  string patron_info;
  patron_info = name + " " + phone + "\n\n";

  return patron_info;
}

class Publication {
  private:
    string title;
    string author;
    string copyright;
    string isbn;
    string patron_name;
    string patron_phone;
    string genre;
    string age;
    string media;
    bool checked_out;

  public:
    Publication(string _title, string _author, string _copyright, string genre, string age, string media, string isbn);
    void check_out(string patron_name, string patron_phone);
    void check_in();
    bool is_checked_out();
    string to_string();
};

Publication::Publication (string _title, string _author, string _copyright, string _genre, string _age, string _media, string _isbn){
	title = _title;
	author = _author;
	copyright = _copyright;
	genre = _genre;
	age = _age;
	media = _media;
	isbn = _isbn;
}

bool Publication::is_checked_out() {
	return (checked_out = false);
}

void Publication::check_out(string patronName, string patronPhone) {
	if (checked_out == false) {
		patron_name = patronName;
		patron_phone = patronPhone;
		checked_out = true;
		
		string result;
		result = "\"" + title + "\"" + " by " + author + ", " + copyright + " " + "ISBN: " + isbn
				 + "\n" + "Checked out";
				 
		fl_message(result.c_str());
	}
	else {
		fl_message("Book is currently checked out");
	}
}

void Publication::check_in() {
	if (checked_out == true) {
		checked_out = false;
	
		string result;
		result = "\"" + title + "\"" + " has been checked in.";
		fl_message(result.c_str());
	}
	else {
		fl_message("This book is already checked in");
	}
}

string Publication::to_string() {
	string checked;

	if (checked_out == false) {
		checked = "Available for check out\n\n";
	}
	else {
		checked = "Checked out by: " + patron_name + " " + patron_phone +"\n";
	}

	string result = "\"" + title + "\"" + " by " + author + ", " + copyright + " " + "ISBN: " + isbn
	+ "\n" + checked;
    return result;
}

class Library {
  private:
    vector <Publication> publications;
    vector <Patron> patrons;
  public:
    void add_publication(Publication pub);
    void check_out(int publication_index, int patron_index);
    void check_in(int publication_index);
    string publications_to_string();
    int number_of_publications();
    void add_patron(Patron pat);
    string patrons_to_string();
    int number_of_patrons();
};

void Library::add_publication(Publication pub) {
  publications.push_back(pub);
}

string Library::publications_to_string() {
string result;
  for (int i = 0; i < publications.size(); i++) {
  	result += publications[i].to_string();
  }
  return result;
}

void Library::check_out(int publication_index, int patron_index) {
  publications[publication_index].check_out(patrons[patron_index].getName(), patrons[patron_index].getPhone());
}

int Library::number_of_publications() {
  return publications.size();
}

void Library::check_in(int publication_index) {
  publications[publication_index].check_in();
}

void Library::add_patron(Patron pat) {
  patrons.push_back(pat);
}

string Library::patrons_to_string() {
string result;
  for (int i = 0; i < patrons.size(); i++) {
	result += patrons[i].to_string();
  }
  return result;
}

int Library::number_of_patrons() {
  return patrons.size();
}

Library library;

void create_publication(Fl_Widget* w, void* p);
void cancel_publication(Fl_Widget* w, void* p);
void create_patron(Fl_Widget* w, void* p);
void cancel_patron(Fl_Widget* w, void* p);
void checkout(Fl_Widget* w, void* p);
void cancel_checkout(Fl_Widget* w, void* p);
void checkin(Fl_Widget* w, void* p);
void cancel_checkin(Fl_Widget* w, void* p);

class Checkin_Dialog {
	public:
		Checkin_Dialog() {
			dialog = new Fl_Window(340, 80, "Check in Book");
				ci_index = new Fl_Input(120, 10, 210, 25, "Index:");
				ci_index->align(FL_ALIGN_LEFT);
				
				ci_create = new Fl_Return_Button(145, 50, 120, 25, "Check In");
				ci_create->callback((Fl_Callback *)checkin, 0);
				
				ci_cancel = new Fl_Button(270, 50, 60, 25, "Cancel");
				ci_cancel->callback((Fl_Callback *)cancel_checkin, 0);
				dialog->end();
				dialog->set_non_modal();
		}
	
		void show() {dialog->show();}
		void hide() {dialog->hide();}
		string index() {return ci_index->value();}
	
	private:
		Fl_Window *dialog;
		Fl_Input *ci_index;
		Fl_Return_Button *ci_create;
		Fl_Button *ci_cancel;
};

class Checkout_Dialog {
	public:
		Checkout_Dialog() {
			dialog = new Fl_Window(340, 100, "Check out Book");
				co_pubIndex = new Fl_Input(120, 10, 210, 25, "Publication Index:");
				co_pubIndex->align(FL_ALIGN_LEFT);
			
				co_nameIndex = new Fl_Input(120, 40, 210, 25, "Name Index:");
				co_nameIndex->align(FL_ALIGN_LEFT);
				
				co_create = new Fl_Return_Button(145, 70, 120, 25, "Check Out");
				co_create->callback((Fl_Callback *)checkout, 0);
				
				co_cancel = new Fl_Button(270, 70, 60, 25, "Cancel");
				co_cancel->callback((Fl_Callback *)cancel_checkout, 0);
				dialog->end();
				dialog->set_non_modal();
		}
		
		void show() {dialog->show();}
		void hide() {dialog->hide();}
		string pubIndex() {return co_pubIndex->value();}
		string nameIndex() {return co_nameIndex->value();}
	private:
		Fl_Window *dialog;
		Fl_Input *co_pubIndex;
		Fl_Input *co_nameIndex;
		Fl_Return_Button *co_create;
		Fl_Button *co_cancel;
};

class Patron_Dialog {
	public:
		Patron_Dialog() {
			dialog = new Fl_Window(340, 130, "New Patron");
				pa_name = new Fl_Input(120, 10, 210, 25, "Patron Name:");
				pa_name->align(FL_ALIGN_LEFT);
				
				pa_phone = new Fl_Input(120, 40, 210, 25, "Patron Phone:");
				pa_phone->align(FL_ALIGN_LEFT);
				
				pa_create = new Fl_Return_Button(145, 100, 120, 25, "Create");
				pa_create->callback((Fl_Callback *)create_patron, 0);
				
				pa_cancel = new Fl_Button(270, 100, 60, 25, "Cancel");
				pa_cancel->callback((Fl_Callback *)cancel_patron, 0);
				dialog->end();
				dialog->set_non_modal();
		}
		
		void show() {dialog->show();}
		void hide() {dialog->hide();}
		string name() {return pa_name->value();}
		string phone() {return pa_phone->value();}
		
	private:
		Fl_Window *dialog;
		Fl_Input *pa_name;
		Fl_Input *pa_phone;
		Fl_Return_Button *pa_create;
		Fl_Button *pa_cancel;
};	
		
class Publication_Dialog {
	public:
		Publication_Dialog() {
			dialog = new Fl_Window(340, 270, "New Publication");
				pb_title = new Fl_Input(120, 10, 210, 25, "Title:");
				pb_title->align(FL_ALIGN_LEFT);
				
				pb_author = new Fl_Input(120, 40, 210, 25, "Author:");
				pb_author->align(FL_ALIGN_LEFT);
				
				pb_copyright = new Fl_Input(120, 70, 210, 25, "Copyright:");
				pb_copyright->align(FL_ALIGN_LEFT);
				
				pb_genre = new Fl_Input(120, 100, 210, 25, "Genre:");
				pb_genre->align(FL_ALIGN_LEFT);
				
				pb_age = new Fl_Input(120, 130, 210, 25, "Age Group:");
				pb_age->align(FL_ALIGN_LEFT);
				
				pb_media = new Fl_Input(120, 160, 210, 25, "Media:");
				pb_media->align(FL_ALIGN_LEFT);
				
				pb_isbn = new Fl_Input(120, 190, 210, 25, "ISBN:");
				pb_isbn->align(FL_ALIGN_LEFT);
				
				pb_create = new Fl_Return_Button(145, 240, 120, 25, "Create");
				pb_create->callback((Fl_Callback *)create_publication, 0);
				
				pb_cancel = new Fl_Button(270, 240, 60, 25, "Cancel");
				pb_cancel->callback((Fl_Callback *)cancel_publication, 0);
			dialog->end();
			dialog->set_non_modal();
		}
		
		void show() {dialog->show();}
		void hide() {dialog->hide();}
		string title() {return pb_title->value();}
		string author() {return pb_author->value();}
		string copyright() {return pb_copyright->value();}
		string genre() {return pb_genre->value();}
		string age() {return pb_age->value();}
		string media() {return pb_media->value();}
		string isbn() {return pb_isbn->value();}
		
	private:
		Fl_Window *dialog;
		Fl_Input *pb_title;
		Fl_Input *pb_author;
		Fl_Input *pb_copyright;
		Fl_Input *pb_genre;
		Fl_Input *pb_age;
		Fl_Input *pb_media;
		Fl_Input *pb_isbn;
		Fl_Return_Button *pb_create;
		Fl_Button *pb_cancel;
};

Patron_Dialog *pat_dlg;

void create_patron(Fl_Widget* w, void* p) {
	string name = pat_dlg->name();
	string phone = pat_dlg->phone();
	
	string result;
	
	Patron pat (name, phone);
	pat_dlg->hide();
	library.add_patron(pat);
	
	result = "New patron added!\n*****************\n" + pat.to_string();
	
	fl_message(result.c_str());
}

void cancel_patron(Fl_Widget* w, void* p) {
	pat_dlg->hide();
}

Publication_Dialog *pub_dlg;

void create_publication(Fl_Widget* w, void* p) {
	string title = pub_dlg->title();
	string author = pub_dlg->author();
	string copyright = pub_dlg->copyright();
	string genre = pub_dlg->genre();
	string age = pub_dlg->age();
	string media = pub_dlg->media();
	string isbn = pub_dlg->isbn();
	
	string result;
	
	Publication pub (title, author, copyright, genre, age, media, isbn);
	pub_dlg->hide();
	
	pub.is_checked_out();
	library.add_publication(pub);
	
	result = "New publication added!\n**********************\n" + pub.to_string();
	fl_message(result.c_str());
}

void cancel_publication(Fl_Widget* w, void* p) {
	pub_dlg->hide();
}

Checkout_Dialog *chkout_dlg;

void checkout(Fl_Widget* w, void* p) {
	string pubIndex = chkout_dlg->pubIndex();
	string nameIndex = chkout_dlg->nameIndex();
	library.check_out(atoi(pubIndex.c_str()), atoi(nameIndex.c_str()));
	chkout_dlg->hide();
}

void cancel_checkout(Fl_Widget* w, void* p) {
	chkout_dlg->hide();
}

Checkin_Dialog *chkin_dlg;

void checkin(Fl_Widget* w, void* p) {
	string index = chkin_dlg->index();
	
	library.check_in(atoi(index.c_str()));
	chkin_dlg->hide();
}

void cancel_checkin(Fl_Widget* w, void* p) {
	chkin_dlg->hide();
}

int execute_cmd(string cmd) {
    if (cmd == "0") {
        exit(1);
    }

    else if (cmd == "1") {
		pub_dlg = new Publication_Dialog{};
		pub_dlg->show();
		return Fl::run();
	}

    else if (cmd == "2") {
      if (library.number_of_publications() > 0) {
      	fl_message_icon()->label("P");
      	fl_message_title("Publications");
        fl_message(library.publications_to_string().c_str());
      }
      else {
      	fl_message_icon()->label("P");
      	fl_message_title("Error");
        fl_message("There are no publications currently in the library");
      }
    }

    else if (cmd == "3") {
      if (library.number_of_publications() > 0) {
        chkout_dlg = new Checkout_Dialog{};
        chkout_dlg->show();
        return Fl::run();
      }
      else {
      	fl_message_icon()->label("P");
      	fl_message_title("Error");
        fl_message("There are no publications currently in the library");
      }
    }

    else if (cmd == "4") {
      if (library.number_of_publications() > 0) {
        chkin_dlg = new Checkin_Dialog{};
        chkin_dlg->show();
        return Fl::run();
      }
      else {
      	fl_message_icon()->label("P");
      	fl_message_title("Error");
        fl_message("There are no publications currently in the library");
      }
    }

    else if (cmd == "5") {
    	pat_dlg = new Patron_Dialog{};
    	pat_dlg->show();
    	return Fl::run();
    }

    else if (cmd == "6") {
      if (library.number_of_patrons() > 0) {
      	fl_message_icon()->label("P");
      	fl_message_title("Patrons");
        fl_message(library.patrons_to_string().c_str());
      }
      else {
      	fl_message_icon()->label("P");
      	fl_message_title("Error");
        fl_message("There are no publications currently in the library");
      }
    }

    else if (cmd == "9") {
		string msg;
      	msg = "Welcome to the C1325 library management system\n";
      	msg += "You can add, check in, or check out a publication, or view a list of all publication\n";
      	msg += "You may also create a new patron or view a list of all patrons\n";
      	msg += "Enter either 1, 2, 3, 4, 5, 6, 9, or 0, depending on what you would like to do";
      	
      	fl_message_icon()->label("H");
      	fl_message_title("Help");
      	fl_message(msg.c_str());
    }
}

int show_menu() {
string command;

while (true) {

	string msg = "===============================\n";
	msg += "C1325 Library Management System\n";
	msg += "===============================\n\n";
	msg += "Publications\n";
	msg += "------------\n";
	msg += "(1) Add publication\n";
	msg += "(2) List all publications\n";
	msg += "(3) Check out publication\n";
	msg += "(4) Check in publication\n\n";
	msg += "Patrons\n";
	msg += "-------\n";
	msg += "(5) Add patron\n";
	msg += "(6) List all patrons\n\n";
	msg += "Utility\n";
	msg += "-------\n";
	msg += "(9) Help\n";
	msg += "(0) Exit\n\n";
	msg+= "Command?";

	Fl_Window *beacon = new Fl_Window(1, 1);
	beacon->show();
	beacon->hide();

	fl_message_icon()->label("L");
	command = fl_input(msg.c_str());
	
	execute_cmd(command);
	}
}

int main() {
show_menu();
}
