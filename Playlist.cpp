#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <limits>
#include <stack>
#include <queue>

using namespace std;

class visualDisplay {
public:
	void storageBar() {
		system("COLOR 02");
		system("cls");
		printf("\e[?25l");
		SetConsoleCP(437);
		SetConsoleOutputCP(437);
		int bar1 = 177, bar2 = 219;
		cout << "\t\t\t\t\t\t  Loading....";
		cout << "\n\n\t\t\t\t\t"; 
		for (int i = 0; i < 30; i++) {
			cout <<(char)bar1;
		}
		cout << "\r\t\t\t\t\t";
		for (int i = 0; i < 30; i++) {
			cout <<(char) bar2;
			Sleep(150);
		}
		cout << "\n\t\t\t\t\t"; 
		system("pause");
		system("cls");
	}
};

//Blueprint of the song
struct Song 
{
    string title;
    string artist;
    string duration;

    Song(string _title, string _artist, string _duration) : title(_title), artist(_artist), duration(_duration){}
};

//Blueprint of the node
struct Node 
{
    Song song;
    Node* next;

    Node(Song _song) : song(_song), next(NULL) {}
};

//Playlist Class
class playlist
{
private:
    Node* head;
    stack<Song> songStack; //Stack for playing songs
    queue<Song> songQueue; //Queue for song requests

public:
    playlist() : head(NULL) {}

	//Prints out the menu
	void showMenu()
	{
		cout << "================= Pick an option =================\n"
                     << "| Type 1: To insert a song to your playlist      |\n"
                     << "| Type 2: To delete a song in your playlist      |\n"
                     << "| Type 3: To search a song in your playlist      |\n"
                     << "| Type 4: To sort your playlist                  |\n"
                     << "| Type 5: To display all songs in your playlist  |\n"
                     << "| Type 6: To play a song                         |\n"
                     << "| Type 7: To quit                                |\n"
                     << "==================================================\n";
	}

    //inserts song at the end of the list
    void insertSong(Song song)
    {
        Node* newNode = new Node(song);
        //If the list is empty. This code defines the newNode as the new head node
        if(!head)
        {
            head = newNode;
            return;
        }
        //Inserts the song at the end of the playlist
        else
        {
         Node* last = head;
         while(last->next != NULL)
            {
                last = last->next;
            }
            last->next = newNode;
        }
    }

    //Deletes a song in the playlist
    void deleteSong(string target)
    {
        //Prints if the playlist is empty
        if(!head)
        {
            cout << "\n~~~~~ There is nothing to delete ~~~~~\n"
                 << "  ~~~~~ The playlist is empty ~~~~~\n";
                 return;
        }
        //Deletes the song if it is the head node
        if(head->song.title == target)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
            cout << "The song [" << target << "] has been deleted.\n";
            return;
        }
        //Traverses the playlist to find the song same as the target
        Node* temp = head;
        while(temp->next && temp->next->song.title != target)
        {
            
            temp = temp->next;
        }
        //Deletes the song in the playlist
        if(temp->next != NULL)
        {
            Node* toDelete = temp->next;
            temp->next = toDelete->next;
            delete toDelete;
            cout << "The song [" << target << "] has been deleted.\n";
            return;
        }
        //Prints out if the target song does not exist in the playlist
        else
        {
            cout << "The song [" << target << "] does not exist in the playlist.\n";
            return;
        }
    }

    //Looks for a specific song in the playlist
    void searchSong(string title)
    {
        if(!head)
        //Prints if the list is empty.
        {
            cout << "  ~~~~~ The playlist is empty ~~~~~\n";
        }
        //traverses the list in order to find the song that is targeted
        Node* temp = head;
        int index = 1;
        bool found = false;
        while(temp)
        {
            if(temp->song.title == title) 
            //Prints when the index/position of the song when it is found
            {
                cout << "Found the song (" << title << ") at position [" << index
                << "] " << temp->song.title << " - " << temp->song.artist << " " << endl;
                found = true;
            }
            temp = temp->next;
            index++;
        }
        //Prints out when the given song title is not in the playlist
        if(found == false)
        {
            cout << "The song (" << title << ") is not in the playlist\n";
        }
    }

    //Function to 'play' specific song that the user wants
    void playSong(string title)
    {
        //Look for the song in the playlist
        Node* temp = head;
        while(temp)
        {
            if(temp-> song.title == title)
            {
                //Push the song onto the stack
                songStack.push(temp->song);
                cout << "\nNow Playing: " << temp->song.title << " - " << temp->song.artist << " (" << temp->song.duration << ") " << endl;
                return;
            }
            temp = temp->next;
        }
        //Print out when the given song title is not in the playlist
        cout << "\nThe song (" << title << ") is not in the playlist." << endl;
    }

    //Stops the song currently in the stack 
    void stopSong()
    {
        if(!songStack.empty())
        {
            Song song = songStack.top();
            cout << "\nStopped Playing: " << song.title << " - " << song.artist << endl;
            songStack.pop();
        }
        else
        {
            cout << "\n~~~~~ No song is currently playing ~~~~~\n";
        }
    }

    //Function to add a specific song to the current song queue
    void requestSong(string title)
    {
        bool found = false;
        //Looks for the song in the playlist
        Node* temp = head;
        while(temp)
        {
            if(temp->song.title == title)
            {
                //Queues the requested song
                songQueue.push(temp->song);
                cout << "\nSong added to your queue: " << temp->song.title << " - " << temp->song.artist << " (" << temp->song.duration << ") " << endl;
                found = true;
                break;
            }
            temp = temp->next;
        }
        if(!found)
        {
            cout << "\nThe song (" << title << ") is not in the playlist." << endl;
        }
    }

    //Plays the next song in the queue
    void playNext()
    {
        if(songQueue.empty())
        {
            cout << "\n~~~~~ No song is currently playing / You haven't queued any song ~~~~~\n";
        }
        else
        {
            if(!songQueue.empty())
            {
                Song song = songQueue.front();
                cout << "\nNow Playing Queued Song: " << song.title << " - " << song.artist << " (" << song.duration << ") " << endl;
                songQueue.pop();
            }
        }
    }    

    //Prints ouf the whole song queue
    void showQueue()
    {
        if(songQueue.empty())
        {
            cout << "\n~~~~~ The song queue is empty ~~~~~" << endl;
            return;
        }
        
        cout << "\n~~~~~~ Queue ~~~~~\n";
        queue<Song> tempQueue = songQueue; //creates a temporary copy to preserve original song queue

        while(!tempQueue.empty())
        {
            Song song = tempQueue.front();
            cout << "~ " << song.title << " - " << song.artist << " (" << song.duration << ") " << endl;
            tempQueue.pop();
        }
    }

    //Sorts the song alphabetically by song name with the use of a 1D array
    void sortSong()
    {
        if (!head) //Prints out if the playlist is empty
        {
            cout << "\n~~~~~ The playlist is empty. Nothing to sort ~~~~~\n";
            return;
        }

        int size = 0;
        Node* temp = head;

        // Count the number of songs in the playlist
        while (temp)
        {
            size++;
            temp = temp->next;
        }

        // Create an array of pointers to store songs
        Song** songs = new Song*[size];

        temp = head;
        int index = 0;

        // Copy song pointers to the array
        while (temp)
        {
            songs[index] = &(temp->song);
            temp = temp->next;
            index++;
        }

        // Sort the array of song pointers
        for (int i = 0; i < size - 1; i++)
        {
            for (int j = 0; j < size - i - 1; j++)
            {
                if (songs[j]->title > songs[j + 1]->title)
                {
                    Song* tempSong = songs[j];
                    songs[j] = songs[j + 1];
                    songs[j + 1] = tempSong;
                }
            }
        }

        // Create a new sorted linked list
        Node* sortedHead = new Node(*(songs[0]));
        Node* current = sortedHead;

        for (int i = 1; i < size; i++)
        {
            current->next = new Node(*(songs[i]));
            current = current->next;
        }

        // Update the playlist with the sorted songs
        head = sortedHead;

        delete[] songs;
        cout << "\nPlaylist sorted alphabetically by song name.\n"
             << "Type Option '5' to display your playlist.\n";
    }

    //Sorts the song alphabetically by artist name with the use of a 1D array
    void sortSongArtist()
    {
        if (!head) //Prints out if the playlist is empty
        {
            cout << "\n~~~~~ The playlist is empty. Nothing to sort ~~~~~\n";
            return;
        }

        int size = 0;
        Node* temp = head;

        // Count the number of songs in the playlist
        while (temp)
        {
            size++;
            temp = temp->next;
        }

        // Create an array of pointers to store songs
        Song** songs = new Song*[size];

        temp = head;
        int index = 0;

        // Copy song pointers to the array
        while (temp)
        {
            songs[index] = &(temp->song);
            temp = temp->next;
            index++;
        }

        // Sort the array of song pointers
        for (int i = 0; i < size - 1; i++)
        {
            for (int j = 0; j < size - i - 1; j++)
            {
                if (songs[j]->artist > songs[j + 1]->artist)
                {
                    Song* tempSong = songs[j];
                    songs[j] = songs[j + 1];
                    songs[j + 1] = tempSong;
                }
            }
        }

        // Create a new sorted linked list
        Node* sortedHead = new Node(*(songs[0]));
        Node* current = sortedHead;

        for (int i = 1; i < size; i++)
        {
            current->next = new Node(*(songs[i]));
            current = current->next;
        }

        // Update the playlist with the sorted songs
        head = sortedHead;

        delete[] songs;
        cout << "\nPlaylist sorted alphabetically by artist name.\n"
             << "Type Option '5' to display your playlist.\n";
    }

    //Displays the whole playlist
    void displaySong()
    {   
        //Prints out if the list is empty
        if(!head)
        {
            cout << "\n~~~~~ There is nothing to display ~~~~~\n"
                 << "  ~~~~~ The playlist is empty ~~~~~\n";
            return;
        }
        Node* temp = head;
        //Index number for aesthetic purposes hahaha
        int index = 1;
        //Prints out the whole list along with the index
        while(temp)
        {
            cout << "[" << index << "] " << temp->song.title << " - " << temp->song.artist << " ("<< temp->song.duration << ")" <<endl;
            temp = temp->next;
            index++;
        }
    }
};

int main() {
	
	visualDisplay access;
	access.storageBar();
	
    playlist p;
    
    cout << "\n\n~~~~~~~~~~~~ Welcome to your Playlist ~~~~~~~~~~~~\n"
         << "================= Pick an option =================\n"
         << "| Type 1: To insert a song to your playlist      |\n"
         << "| Type 2: To delete a song in your playlist      |\n"
         << "| Type 3: To search a song in your playlist      |\n"
         << "| Type 4: To sort your playlist                  |\n"
         << "| Type 5: To display all songs in your playlist  |\n"
         << "| Type 6: To play a song                         |\n"
         << "| Type 7: To quit                                |\n"
         << "==================================================\n";

    //Promts the user to pick an option
    while(true)
    {
        int choice;
        string songName, songArtist, songDuration;
        cout << "\nEnter option (1-7): ";
        cin >> choice;

    if (cin.fail()) //Checks if the choice input was not an integer //Without this the program would infinitely loop when inputing a non-integer option
        {
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line
            cout << "\n~~ Invalid input. Please enter a valid option (1-7) ~~\n";
            system("pause");
			system("cls");
			p.showMenu();
        }
        else
        {
            if(choice == 1) //Calls the insert function
            {
                cin.ignore();
                cout << "Enter song name: ";
                getline(cin, songName);
                cout << "Enter song artist: ";
                getline(cin, songArtist);
                cout << "Enter song duration: ";
                getline(cin, songDuration);

                p.insertSong(Song(songName, songArtist, songDuration));
                cout << "\n(" << songName << " - " << songArtist << ") has been inserted to your playlist.\n";
                system("pause");
				system("cls");
				p.showMenu();
            }
            else if(choice == 2) //Calls the delete function
            {
                cin.ignore();
                cout << "Enter song name to delete: ";
                getline(cin, songName);

                p.deleteSong(songName);
                
                system("pause");
				system("cls");
				p.showMenu();
            }
            else if(choice == 3) // Calls the search function
            {
                cin.ignore();
                cout << "Enter song name that you are looking for: ";
                getline(cin, songName);

                p.searchSong(songName);
                
                system("pause");
				system("cls");
				p.showMenu();
            }
            else if(choice == 4) // Calls the sort function
            {
                while (true) {
                int choice;
                cout << "\n=======================================================\n"
                     << "| Type 1: To sort songs alphabetically by song name   |\n"
                     << "| Type 2: To sort songs alphabetically by song artist |\n"
                     << "=======================================================\n"
                     << "Enter option (1-2): ";
                cin >> choice;
                    if(choice == 1)
                    {
                        p.sortSong();
                        system("pause");
						system("cls");
						p.showMenu();
                        break;
                    }
                    else if(choice == 2)
                    {
                        p.sortSongArtist();
                        system("pause");
						system("cls");
						p.showMenu();
                        break;
                        
                    }
                    else
                    {
                        cout << "\nInvalid input. Please enter a valid option (1-2).\n\n";
                    }
                }
            }
            else if(choice == 5) //Calls the display function
            {
                cout << "\n~~~~~ Songs in your playlist ~~~~~\n";
                p.displaySong();
                
                system("pause");
				system("cls");
				p.showMenu();
            }
            else if(choice == 6) //Prompts user to play|play(next song)/stop/queue/ a specific song & shows the current queue of songs
            {
            system("pause");
			system("cls");
                while(true)
                {

                cout << "\n================ Pick an option ================\n"
                     << "| Type 'play': To play a song in your playlist |\n"
                     << "| Type 'stop': To stop currently playing song  |\n"
                     << "| Type 'next': To play next song in your queue |\n"
                     << "| Type 'add': To add a song to your queue      |\n"
                     << "| Type 'queue': To show your queue list        |\n"
                     << "| Type 'mod': To modify your playlist          |\n"
                     << "================================================\n";

                    string subChoice;
                    cout << "\nEnter option: ";
                    cin >> subChoice;

                    if(subChoice == "play")
                    {
                        cin.ignore();
                        cout << "Enter song name that you want to play: ";
                        getline(cin, songName);

                        p.playSong(songName);
                        
                        system("pause");
						system("cls");
                    }
                    else if(subChoice == "stop")
                    {
                        p.stopSong();
                        
                        system("pause");
						system("cls");
                    }
                    else if(subChoice == "next")
                    {
                        p.stopSong();
						p.playNext();
						
						system("pause");
						system("cls");
                    }
                    else if(subChoice == "add")
                    {
                        cin.ignore();
                        cout << "Enter song name that you want to play: ";
                        getline(cin, songName);

                        p.requestSong(songName);
                        
                        system("pause");
						system("cls");
                    }
                    else if(subChoice == "queue")
                    {
                        p.showQueue();
                        
                        system("pause");
						system("cls");
                    }
                    else if(subChoice == "mod")
                    {
                    	system("pause");
						system("cls");
						p.showMenu();
                        break;
                    }
                    else
                    {
                        cout << "~~~ Invalid input. Ensure you are typing in lowercase and check your spellings. ~~~\n";
                        system("pause");
						system("cls");
                    }
                }
            }
            else if(choice == 7) //Exits the program
            { 
                char agree;
                cout << "\n================================================================\n" 
                     << "| Are you sure you want to quit? Type 'y' if yes and 'n' if no |"
                     << "\n================================================================\n"
                     << "(y / n): "; 
                cin >> agree;
                if (agree == 'y' || agree == 'Y')
                {
                    cout << "\n~~~~~ Program ended ~~~~~\n";
                    exit(0);
                }
                else if (agree == 'n' || agree == 'N')
                {
                    cout << "\n~~~~~~~~~ Proceeding back to menu ~~~~~~~~~\n";
                    system("pause");
					system("cls");
					p.showMenu();
                    // Continue with the menu
                }
                else
                {
                    cout << "\n~~~~~~~~~ You can only choose between 'y' and 'n' ~~~~~~~~~\n";
                }
            }
            else //Prints out if user input is not in the choices
            {
                cout << "\n====================================================\n" 
                     << "| Invalid input. Please enter a valid option (1-7) |\n"
                     << "====================================================\n" ;
                    system("pause");
					system("cls");
					p.showMenu();
            }
        }
    }
    return 0;
}
