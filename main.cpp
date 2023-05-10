#include <iostream>
#include <cstring>
#include <string>
#include <map>
#include <fstream>
using namespace std;

class Persoana
{
    char *nume;
    int varsta;

    public:
        Persoana(){nume=NULL; varsta=0;}

        Persoana(char *n, int v):nume(n),varsta(v) {}

        Persoana(const Persoana &p)
        {
            nume=NULL;
            *this=p;
        }

        Persoana &operator=(const Persoana &p)
        {
            if (nume!=NULL) delete[]nume;
            nume=new char[strlen(p.nume)+1];
            strcpy(nume,p.nume);
            varsta=p.varsta;
            return *this;
        }

        friend ostream &operator<<(ostream & dev,Persoana &p)
        {
            dev<<p.nume<<" "<<p.varsta;
            return dev;
        }

        friend bool operator<(const Persoana& p1, const Persoana& p2)
        {
		return (p1.nume < p2.nume);
	    }

        ~Persoana()
        {
            if (nume!=NULL) delete[]nume;
        }
};

class Album
{
	int an_aparitie;
	string nume;
	map<int,string> track;

    public:
        Album()
        {
            an_aparitie = 0;
            nume = " ";
            track.insert(pair<int, string>(0, " "));
        }

        Album(int an, string n,map<int,string> t):an_aparitie(an), nume(n),track(t) {}

        Album(const Album &a):an_aparitie(a.an_aparitie), nume(a.nume), track(a.track) {}

        Album& operator=(const Album &a)
        {
            an_aparitie = a.an_aparitie;
            nume = a.nume;
            track = a.track;
            return *this;
        }

        friend ostream &operator<<(ostream &dev, const Album &a)
        {
            dev <<"\tAn aparitie: " << an_aparitie << "\tNume: " << nume << endl;
            for (map<int,string>::iterator it = track.begin(); it!=track.end();it++)
            {
			dev << "\tTrack: " << it->first<<" "<<it->second<<endl;
            }
            return dev;
        }

        friend bool operator<(const Album &a1,const Album &a2)
        {
            if (a1.an_aparitie == a2.an_aparitie)
                return (a1.nume < a2.nume);
            return (a1.an_aparitie < a2.an_aparitie);
        }

        int getAn()
        {
            return an_aparitie;
        }

        void adaugaTrack(pair<int, string> t)
        {
		track.insert(t);
        }

        void elimTrack(int n)
        {
		map<int,string>::iterator it=track.find(n);
		track.erase(it);
        }

        void modifTrack(int n, string track_nou)
        {
		map<int, string>::iterator it = track.find(n);
		it->second = track_nou;
        }
};

class Artist :public Persoana
{
	multimap<int,Album> Colectie;

    public:
        Artist()
        {
            Colectie.insert(pair<int,Album>(0,Album()));
        }

        Artist(string n, int v, multimap<int,Album> a):Persoana(n, v),Colectie(a){}

        Artist(const Artist &a):Persoana(a.nume, a.varsta), Colectie(a.Colectie) {}

        Artist &operator=(const Artist &a)
        {
            nume = a.nume;
            varsta = a.varsta;
            Colectie = a.Colectie;
            return *this;
        }

        friend ostream &operator<<(ostream &dev, const Artist &a)
        {
            dev << a.nume << " " << a.varsta << endl;
            for (multimap<int, Album>::iterator it = Colectie.begin(); it != Colectie.end(); it++)
                {
                dev << "\t";
                dev<<it->second;
                }
            return dev;
        }

        friend bool operator<(const Artist &a1, const Artist &a2)
        {
            if (strcmp(a1.nume,a2.nume)==1)
                return(a1.varsta < a2.varsta);
            return (a1.nume < a2.nume);
        }

        void adaugaAlbum(pair<int, Album> t)
        {
            Colectie.insert(t);
        }

        void elimAlbum(int n)
        {
		multimap<int, Album>::iterator it = Colectie.find(n);
		Colectie.erase(it);
        }

        void modifAlbum(int n, Album album_nou)
        {
		multimap<int, Album>::iterator it = Colectie.find(n);
		it->second = album_nou;
        }
};

int main()
{
        fstream fis("Artisti.txt",ios::app);
        if (!fis) cout<<"Eroare la deschiderea fisierului";
        map<int,string> songs;
        pair<int,string> t1(1, "All I want for Christmas is you");
        pair<int,string> t2(2, "Last Christmas");
        pair<int,string> t3(3, "Jingle Bells");
        pair<int,string> t4(4, "Let it snow");
        songs.insert(t1);
        songs.insert(t2);
        songs.insert(t3);
        songs.insert(t4);
        Album a(2002, "Colinde de Craciun", songs);
        songs.insert(pair<int,string>(5,"Frosty the Snowman"));
        Album b(2005, "Alte colinde de Craciun", songs);
        songs.erase(2);
        Album c(2006, "Si mai multe colinde de Craciun",songs);
        cout<<a<<" "<<b<<" "<<c<<endl;

        //Eliminare track
        b.elimTrack(1);
        cout<<b<<endl;

        //Adaugare track
        a.adaugaTrack(pair<int,string>("5","Sleigh Ride"));
        cout<<a<<endl;

        //Modificare track
        c.modifTrack(1,"O Christmas Tree");
        cout<<c<<endl;

        multimap<int,Album> albume;
        albume.insert(pair<int,Album>(c.getAn(),c));
        albume.insert(pair<int,Album>(a.getAn(),a));
        albume.insert(pair<int,Album>(b.getAn(),b));
        Artist muzician("Un cantaret oarecare",43,albume);
        cout<<muzician;

        //Eliminare album
        muzician.elimAlbum(b.getAn());
        cout<<muzician<<endl;

        //Adaugare album
        muzician.adaugaAlbum(pair<int,Album>(c.getAn(),c));
        cout<<muzician<<endl;

        //Modificare album
        muzician.modifAlbum(a.getAn(),b);
        cout<<muzician<<endl;

        fis.close();
        return 0;
}
