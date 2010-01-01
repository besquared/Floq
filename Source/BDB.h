#ifndef _flow_bdb_h_
#define _floq_bdb_h_

#include "Common.h"

using namespace std;

namespace Floq {
	class BDB {
	protected:
		string path;
		string name;
		TCBDB *database;
		pthread_mutex_t mutex;
    
	public:		
		BDB(const string& path, const string& name);
		virtual ~BDB();
		
		bool OpenReader();
		bool OpenWriter();
		bool Open(int mode);
		bool Close();
		bool Truncate();
		
		void Lock();
    void Unlock();
    
		bool Get(const string& key, string& result);	
    bool Get(BDBCUR* cursor, string& result);
    bool Get(const string& key, vector<string>& results);
		bool Put(const string& key, const string& value);
		bool PutDup(const string& key, const string& value);
		bool Add(const string& key, const int value, int& result);
		bool Out(const string& key);
    int Count(const string& key);
    
    bool TransactionBegin();
    bool TransactionAbort();
    bool TransactionCommit();
  
		string Error();
		int ErrorCode();
		
		static bool Create(const string& path, const string& name);
		static string Path(const string& path, const string& name);
	};
}

#endif