#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<fstream>
#include<iostream>
#include<map>
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <vector>
#include<regex>
#include<iomanip>
#include<conio.h>


using namespace std;


#define alphasize 26

#define chartoind(c) ((int)c - (int)'a')



vector<string> names;

struct TrieNode
{
    struct TrieNode *children[alphasize+1];

    string number;


    int is_end_of_word;
    string email;
    string address;

    string name;
};


inline string convertToString(char* a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}








struct TrieNode *getNode()
{
    struct TrieNode *node = new TrieNode;

    if(node!=NULL)
    {
        int i;
        node->is_end_of_word = 0;

        for (i = 0; i < alphasize; i++)
        {
            node->children[i] = NULL;
        }
    }

    return node;
}



void insert(struct TrieNode *root, string key,string add,string email_id,string no)
{
    int level;

    int l = key.length();
    int ind;

    if (!root)
    {
        root = getNode();
    }

    struct TrieNode *newnode = root;


    for (level = 0; level < l; level++)
    {
        ind = chartoind(key[level]);
        if (!newnode->children[ind])

        newnode->children[ind] = getNode();
        newnode = newnode->children[ind];
    }

    newnode->is_end_of_word = 1;


    newnode->number = no;
    newnode->address = add;
    newnode->email = email_id;
    newnode->name = key;


}

TrieNode* search(struct TrieNode *root, string key)
{
    int level;
    int length = key.length();
    int index;
    struct TrieNode *newnode = root;
    for (level = 0; level < length; level++)
    {
        index =chartoind(key[level]);

        if (!newnode->children[index])
        {
            //cout<<"ok_"<<endl;
            return NULL;
        }

        newnode=newnode->children[index];
    }

    return (newnode);
}






bool isLeafNode(struct TrieNode* root)
{
    return root->is_end_of_word!= 0;
}







void traversePrint(TrieNode* sr,char* out,int index)
{
    if(sr!=NULL)
    {
        for(int i=0;i<alphasize;i++)
        {
            if(sr->children[i]!=NULL)
            {
                out[index] = 'a'+i;
                traversePrint(sr->children[i],out,index+1);
            }
        }
        if(sr->is_end_of_word)
        {
            out[index]='\0';
            ///cout << out << endl;

            string j(out);
            ///cout<<j<<endl;
            ///names[++x] = j;
            names.push_back(j);


        }
    }
}







void traversePrint_updated(TrieNode* sr,char* out,int index)
{
    if(sr!=NULL)
    {
        for(int i=0;i<alphasize;i++)
        {
            if(sr->children[i]!=NULL)
            {
                out[index] = 'a'+i;
                traversePrint(sr->children[i],out,index+1);
            }
        }
        if(sr->is_end_of_word)
        {
            out[index]='\0';
            ///cout << out << endl;

            string j(out);
            cout<<j<<endl;
            ///names[++x] = j;


        }
    }
}














void write_into_file(struct TrieNode* x)
{
    fstream fout;

    fout.open("file.txt", ios::out | ios::app);

    fout<<x->name<<"|"<<x->address<<"|"<<x->number<<"|"<<x->email<<endl;

    fout.close();
}







bool isEmpty(TrieNode* root) //check if root has children or not
{
   for (int i = 0; i < alphasize; i++)
   if (root->children[i])
   return false;
   return true;
}






TrieNode* remove(TrieNode* root, string key, int depth = 0)
{


    if (!root)
        return NULL;


    if (depth == key.size()) {


        if (root->is_end_of_word)
            root->is_end_of_word = 0;


        if (isEmpty(root)) {
            delete (root);
            root = NULL;
        }

        return root;
    }



    int index = key[depth] - 'a';
    root->children[index] =
          remove(root->children[index], key, depth + 1);



    if (isEmpty(root) && root->is_end_of_word == 0) {
        delete (root);
        root = NULL;
    }

    return root;
}




void input_file(TrieNode * root)
{
    ifstream file("file.txt", ios::in);

    string name, address, email, phone;

    // Tokenizing w.r.t. space ' '
    while(getline(file, name, '|'))
    {
        getline(file, address, '|');
        getline(file, phone, '|');
        getline(file, email);
        insert(root, name, address, email, phone);
    }

    // Printing the token vector
    ///for(int i = 0; i < tokens.size(); i++)
        /// cout << tokens[i] << '\n';

    // insert(root,tokens[0],tokens[1],tokens[3],tokens[2]);
    file.close();
}




bool isValid_email(const string& email)
{
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

    return regex_match(email, pattern);
}




bool isValid_number(string no)
{
    int count = 0;
    for(int i=0;i<no.length();i++)
    {
        if(no[i] <= '9' && no[i] >= '0')
        {
            count += 1;
        }

        else
            return false;
    }

    if(count == 10)
    {
        return true;
    }
}





int main()
{
    int n1,i1,ch,hi;

    string name;
    string keys;

    ///char output[][32] = {"Not present in Phonebook", "Present in Phonebook"};

    struct TrieNode *root;

    root = getNode();

    input_file(root);

    do
    {

        cout<<"Enter 1 for creating a new contact: ";
        cout<<endl<<"Enter 2 for searching an existing contact: ";
        cout<<endl<<"Enter 3 for updating an existing entry: ";
        cout<<endl<<"Enter 4 for deleting an existing entry: ";
        cout<<endl<<"Enter 5 for displaying all the entries: ";
        cout<<endl<<"Enter 0 for exiting: \t";

        cin>>ch;

        cout<<endl<<endl<<endl;


        switch(ch)
        {
            case 1:
            {
                if(!root)
                {
                    root = getNode();
                }


                string add,email_id;
                string no;

                cout<<endl<<endl<<"Enter the name of the shop (Don't use any special characters and spaces): ";


                cin>>keys;

                cout<<"Enter the address: ";
                getline(cin>>ws, add);
                ///cin.ignore(1,'\n');
                // cin>>add;

                bool a;

                do
                {
                    cout<<"Enter the email-id: ";
                    getline(std::cin>>ws, email_id);

                    a = isValid_email(email_id);

                    if(!a)
                    {
                        cout<<endl<<"Invalid Email-ID...Please enter again"<<endl;
                    }

                }while(!isValid_email(email_id));

                ///cin.ignore(1,'\n');
                // cin>>email_id;

                do
                {

                    cout<<"Enter the contact number: ";
                    getline(std::cin>>ws, no);

                    if(no.length() != 10 || !isValid_number(no))
                    {
                        cout<<endl<<"Invalid contact number...Please enter again"<<endl;
                    }
                }while(no.length() != 10 || !isValid_number(no));


                ///cin.ignore();

                transform(keys.begin(), keys.end(), keys.begin(), ::tolower);

                insert(root,keys,add,email_id,no);

                break;
            }



            case 2:
            {
                if(!root)
                {
                    root = getNode();
                }


                cout<<endl<<endl<<"Enter the name to be Searched: ";

                cin>>name;



                transform(name.begin(), name.end(), name.begin(), ::tolower);


                struct TrieNode *newnode = search(root,name);

                if(newnode != NULL && newnode->number!="")
                {
                    cout<<endl<<endl;
                    cout<<"Name: "<<name;
                    cout<<endl<<"Phone number: "<<newnode->number;
                    cout<<endl<<"Address: "<<newnode->address;
                    cout<<endl<<"Email-ID: "<<newnode->email;
                    cout<<endl;
                }

                else
                {

                    cout<<"Not present in Phonebook"<<endl;
                }

                break;
            }


            case 3:
            {
                if(!root)
                {
                    root = getNode();
                }

                string add,email_id;
                string no,s;

                cout<<endl<<endl<<"Enter the name of the shop whose detail is to updated: ";
                cin>>keys;
                // cin>>keys;
                ///cin.ignore(1,'\n');

                transform(keys.begin(), keys.end(), keys.begin(), ::tolower);

                struct TrieNode *newnode = search(root,keys);


                if(newnode != NULL && newnode->number!="")
                    root = remove(root,keys);

                else
                {
                    cout<<endl<<"Not present in phonebook";
                    goto end_;
                }



                cout<<"Enter the new address: ";
                getline(std::cin>>ws, add);
                ///cin.ignore(1,'\n');
                // cin>>add;

                 bool a;

                do
                {
                    cout<<"Enter the new email-id: ";
                    getline(std::cin>>ws, email_id);

                    a = isValid_email(email_id);

                    if(!a)
                    {
                        cout<<endl<<"Invalid Email-ID...Please enter again"<<endl;
                    }

                }while(!isValid_email(email_id));


                ///cin.ignore(1,'\n');
                // cin>>email_id;

                do
                {

                    cout<<"Enter the new contact number: ";
                    getline(std::cin>>ws, no);

                    if(no.length() != 10 || !isValid_number(no))
                    {
                        cout<<endl<<"Invalid contact number...Please enter again"<<endl;
                    }
                }while(no.length() != 10 || !isValid_number(no));


                 ///cin.ignore(1,'\n');


                ///transform(s.begin(), s.end(), s.begin(), ::tolower);

                if (!root) {
                    root = getNode();
                }
                insert(root,keys,add,email_id,no);

                end_:

                break;
            }


            case 4:
            {
                if(!root)
                {
                    root = getNode();
                }

                string s;
                cout<<endl<<endl<<"Enter the name of shop to be deleted: ";
                cin>>s;
                // cin>>s;

                struct TrieNode *newnode = search(root,s);

                if(newnode != NULL && newnode->number!="")
                    root = remove(root,s);

                else
                {
                    cout<<endl<<"Not present in phonebook";
                    goto end__;
                }

                end__:
                break;
            }

            case 5:
            {

                if(!root)
                {
                    root = getNode();
                }

                if(!isEmpty(root))
                {
                names.clear();

                char str[20];
                int level = 0;

                traversePrint(root,str,0);

                ///cout<<setw(10)<<"Name"<<setw(30)<<"Phone Number"<<setw(20)<<"Address"<<setw(20)<<"Email-ID"<<endl;
                ///cout<<"----------------------------------------------------------------------------------------------"<<endl;

                for(int i=0;i<names.size();i++)
                {


                    struct TrieNode *newnode = search(root,names.at(i));

                    if(newnode != NULL && newnode->number!="")
                    {
                        ///cout<<setw(10)<<"ten"<<"four"<<"four";

                        ///cout<<setw(4)<<newnode->name<<setw(35)<<newnode->number<<setw(25)<<newnode->address<<setw(25)<<newnode->email<<endl;






/*
                        cout<<endl<<endl;
                        cout<<"Name: "<<names[i];
                        cout<<endl<<"Phone number: "<<newnode->number;
                        cout<<endl<<"Address: "<<newnode->address;*/


                        cout<<"Name:           "<<newnode->name<<endl;
                        cout<<"Phone number:   "<<newnode->number<<endl;
                        cout<<"Address:        "<<newnode->address<<endl;
                        cout<<"Email-ID:       "<<newnode->email;

                        cout<<endl;
                        cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;

                        ///write_into_file(newnode);
                    }


                }
                }

                else
                {
                    cout<<endl<<endl<<"Telephone Directory is Empty....";
                }

                break;


            }

            /*case 6:
            {
                char str[20];
                int level = 0;

                traversePrint_updated(root,str,0);
            }*/


        }


        cout<<endl<<endl<<"Press Enter to Continue...";

        getch();

        system("cls");


    }while(ch!=0);



    std::ofstream ofs;
    ofs.open("file.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();


///    x = 0;
    char str[20];
    int level = 0;


    names.clear();
    traversePrint(root,str,0);



    for(int i=0;i<names.size();i++)
    {


        struct TrieNode *newnode = search(root,names.at(i));

        if(newnode != NULL && newnode->number!="")
        {
            write_into_file(newnode);
        }


    }

    return 0;
}
