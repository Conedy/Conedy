
#define BOOST_IOSTREAMS_UNREACHABLE_RETURN(x)   return x;


#ifndef M_PI
#define M_PI    3.14159265358979323846f
#endif

#ifndef ioNode_h
#define ioNode_h ioNode_h

#include "node.h"
//#include "analData.h"
//#include "Tdata.h"

#include "dynNode.h"
#include <iomanip>
#include <map>
#include "globals.h"

#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/device/file.hpp>
namespace io = boost::iostreams;
using namespace std;
// using namespace boost::iostreams::zlib;
// using namespace boost;
using namespace boost::iostreams;

// TODO: Fehlermeldung, wenn Datei nicht geöffnet werden kann. (Wegen Verzeichnis oder so)


#include <iostream>



namespace conedy
{

	class streamOutNodeBinary : public dynNode, private globals
	{

		protected:
			baseType x;

			//! Vector mit allen Ausgabeobjekten.
			static std::vector<ostream*> out;

			//! counter[a] speichert, wieviele Nodes das a.-ten Ausgabeobjekt benutzen.
			static std::map<int, unsigned int> counter;

			//! Zuordnung von Dateinamen zu der Nummer des entsprechenden Ausgabeobjekts im Vector out.
			static std::map<string, int> streamNumber;

			//! zuordnung von der Nummer der Ausgabeobjekte in out zum Namen der Datei, in die geschrieben wird.
			static std::map<int,string> stringOfStreamNumber;

			//! Kleinste Nummer im Ausgabeobjektvector out, die noch nicht verwendet wird.
			static int smallestUnusedNumber;

			//! Nummer des Lokalen Ausgabeobjekts.
			int localStreamNumber;

		public:

			//! Ausgabenodes brauchen keinen Aufruf von evolve, und somit gibt timeEvolution 0 zurück.
			virtual bool timeEvolution () { return 0; }
			//! Ausgabenodes brauchen keinen Speicherplatz von dynNode reserviert zu bekommen -> dimension = 0
			virtual const unsigned int dimension() const { return 0;}

			streamOutNodeBinary ( networkElementType n ) : dynNode( n ) {};



			virtual ~streamOutNodeBinary();
			virtual void evolve(baseType time) {

				x = this->couplingSum();
			out [localStreamNumber]->write ( (char *) &x, sizeof (baseType));
			};
	//		virtual node *construct();



			streamOutNodeBinary ( const streamOutNodeBinary& n ) : dynNode  (n) { localStreamNumber = n.localStreamNumber; counter[localStreamNumber]++; }
			streamOutNodeBinary ( string s, networkElementType n = _streamOutNodeBinary_ );
			//		virtual void streamOut(outStream & out);
			//		streamOutNodeBinary(string s, string command);
			virtual const nodeInfo getNodeInfo() { nodeInfo n = {_streamOutNodeBinary_,_outNode_, "streamOutNodeBinary" };     return n; };

	};


	//! Klasse, die Werte in Dateien wegschreibt. Verwendet Boost-iostreamm damit Dateien direkt on-the-fly gezipt werden können. Die Ausgabeobjekte werden statisch verwaltet, damit verschiedene Nodes in dieselbe Datei schreiben können.
	class streamOutNode : public dynNode, public globals
	{

		protected:
			baseType x;

			//! Vector mit allen Ausgabeobjekten.
			static std::vector<io::filtering_ostream*> out;

			//! counter[a] speichert, wieviele Nodes das a.-ten Ausgabeobjekt benutzen.
			static std::map<int, unsigned int> counter;

			//! Zuordnung von Dateinamen zu der Nummer des entsprechenden Ausgabeobjekts im Vector out.
			static std::map<string, int> streamNumber;

			//! zuordnung von der Nummer der Ausgabeobjekte in out zum Namen der Datei, in die geschrieben wird.
			static std::map<int,string> stringOfStreamNumber;

			//! Kleinste Nummer im Ausgabeobjektvector out, die noch nicht verwendet wird.
			static int smallestUnusedNumber;

			//! Nummer des Lokalen Ausgabeobjekts.
			int localStreamNumber;

		public:

			static void enter();



			//! Ausgabenodes brauchen keinen Aufruf von evolve, und somit gibt timeEvolution 0 zurück.
			virtual bool timeEvolution () { return 0; }
			static void registerStandardValues()
			{
				registerGlobal<bool> ("outputCompress", false);
				registerGlobal<bool> ("outputAppend", false);
				registerGlobal<int> ("outputPrecision", 15);
			}

			//! Ausgabenodes brauchen keinen Speicherplatz von dynNode reserviert zu bekommen -> dimension = 0
			virtual const unsigned int dimension() const { return 0;}

			streamOutNode ( networkElementType n ) : dynNode( n ) {};


			virtual ~streamOutNode();
			virtual void evolve(baseType time) ;
			virtual node *construct()
			{ cout << "I am here" << endl;
				if (getGlobal<bool>("inputCompress"))
				{
					streamOutNodeBinary * blueprint = new streamOutNodeBinary(stringOfStreamNumber[localStreamNumber]);
					return new streamOutNodeBinary (* blueprint );
					delete blueprint;
				}
				else
					return new streamOutNode(*this);
			}

			streamOutNode ( const streamOutNode& n ) : dynNode  (n) { localStreamNumber = n.localStreamNumber; counter[localStreamNumber]++; }
			streamOutNode ( string s, networkElementType n = _streamOutNode_ );
			//		virtual void streamOut(outStream & out);
			//		streamOutNode(string s, string command);

			virtual const nodeInfo getNodeInfo() { nodeInfo n = {_streamOutNode_,_outNode_, "streamOutNode" };     return n; };


	};

	class streamOutNodeCountEquals : public streamOutNode
	{
		baseType lastValue;
		unsigned int count;
		public:
		streamOutNodeCountEquals ( networkElementType n ) : streamOutNode( n ), lastValue (0.0), count (0) {};
		streamOutNodeCountEquals ( string s, networkElementType n = _streamOutNode_ ) : streamOutNode(s, n) {};
		virtual void evolve (baseType time);	
	};
	
	
	class streamOutNodeHist : public streamOutNode
	{
		public:
			static void registerStandardValues()
			{
				registerGlobal<baseType> ("streamOutNodeHist_lowest", 0.0);
				registerGlobal<baseType> ("streamOutNodeHist_highest", 1.0);
				registerGlobal<int> ("streamOutNodeHist_bins", 200);
			}


		streamOutNodeHist ( networkElementType n ) : streamOutNode( n ) {} 
		streamOutNodeHist ( string s, networkElementType n = _streamOutNode_) : streamOutNode(s, n) {};
		virtual void evolve (baseType time);	
	};


	//! Klasse, die Werte in Dateien wegschreibt. Verwendet Boost-iostreamm damit Dateien direkt on-the-fly gezipt werden können. Die Ausgabeobjekte werden statisch verwaltet, damit verschiedene Nodes in dieselbe Datei schreiben können.

	//! Knoten, der die vektorielle Summe Targetstates zurückgibt.
	class calculateMeanPhaseCoherence : public dynNode

		{

		public:

			virtual bool timeEvolution() { return 0; }
			virtual const nodeInfo getNodeInfo() { nodeInfo n = {_calculateMeanPhaseCoherence_,0,"calculateMeanPhaseCoherence"};     return n; };
			virtual const unsigned int dimension() const { return 0;}

			calculateMeanPhaseCoherence() : dynNode(_calculateMeanPhaseCoherence_) {};
			virtual void clean () {};
			virtual baseType getState();
	};



		//! Berechnet die mittlere Phase der angekopplten Knoten aus.
	class calculateMeanPhase : public dynNode
	{
		public:

			virtual bool timeEvolution() { return 0; }
			virtual const nodeInfo getNodeInfo() { nodeInfo n = {_calculateMeanPhase_,_dynNode_|_inNode_,"calculateMeanPhase"};     return n; };
			virtual const unsigned int dimension() const { return 0;}

			calculateMeanPhase() : dynNode(_calculateMeanPhase_) {};
			virtual void clean () {};
			virtual baseType getState();
	};



	//! Eingabe-node, der Werte aus einer Datei liest und bei Aufruf von getState zurückgibt.
	class streamInNode : public dynNode, private globals

	{

		protected:

			static std::vector<io::filtering_istream*> in;
			static std::map<int, unsigned int> counter;
			static std::map<string, int> streamNumber;
			static std::map<int,string> stringOfStreamNumber;
			static int smallestUnusedNumber;
			int localStreamNumber;

			bool inline zipInput() { return ( bool ) getGlobal<bool>("inputCompress");  }
		public:
			virtual bool timeEvolution () { return 0; }
			static void registerStandardValues()
			{
				registerGlobal<bool>("inputCompress", false);
			}
			virtual const unsigned int dimension() const { return 1;}

			streamInNode ( networkElementType n ) : dynNode ( n, 1 ) {};


			virtual ~streamInNode();
			//			streamInNode ( outStream &o, int i ) : node ( i, _streamInNode_ )  {};
			virtual void evolve(baseType time) {   ( * ( in[localStreamNumber] ) ) >> dynNode::x[0]; }; //cout << x << endl; };

//			virtual void swap () { this->state = x; };



			streamInNode ( const streamInNode& n ) : dynNode(n) { localStreamNumber = n.localStreamNumber; counter[localStreamNumber]++; }
			streamInNode ( string s, networkElementType n = _streamInNode_ );
			//		virtual void streamIn(outStream & out);
			//		streamInNode(string s, string command);

			virtual const nodeInfo getNodeInfo() { nodeInfo n = {_streamInNode_,_inNode_|_dynNode_ , "streamInNode"};     return n; };


};


}

#endif
