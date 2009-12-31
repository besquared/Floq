#include "BDB.h"

using namespace Floq;

BDB::BDB(const string& path, const string& name) {
	this->path = path;
	this->name = name;
	this->database = tcbdbnew();
}

BDB::~BDB() {
	this->Close();
  tcbdbdel(this->database);
}

bool BDB::Create(const string& path, const string& name) {
	TCBDB* database = tcbdbnew();
	
	tcbdbtune(database, -1, -1, -1, -1, -1, BDBTLARGE | BDBTDEFLATE);
	if(tcbdbopen(database, BDB::Path(path, name).c_str(), BDBOWRITER | BDBOCREAT)) {
		tcbdbclose(database);
		tcbdbdel(database);
		return true;
	} else {
		tcbdbdel(database);
		return false;
	}
}

string BDB::Path(const string& path, const string& name) {
  return path + "/" + name + ".tcb";
}

bool BDB::OpenReader() {
  return this->Open(BDBOREADER);
}

bool BDB::OpenWriter() {
  return this->Open(BDBOWRITER | BDBOCREAT);
}

bool BDB::Truncate() {
	if(this->Open(BDBOWRITER | BDBOTRUNC)) {
		this->Close();
		return true;
	} else {
		return false;
	}
}

bool BDB::Open(int mode) {
	return tcbdbopen(this->database, BDB::Path(this->path, this->name).c_str(), mode);
}

bool BDB::Close() {	
	return tcbdbclose(this->database);
}

bool BDB::Get(const string& key, string& result) {
	int b_size;
	void* buffer;
	
	buffer = tcbdbget(this->database, key.c_str(), key.size(), &b_size);
	
	if(buffer == NULL) {
		return false;
	} else {
		result.assign((char*)buffer, b_size);
		free(buffer);
		return true;
	}
}

bool BDB::Put(const string& key, const string& value) {
	return tcbdbput(this->database, key.c_str(), key.size(), value.c_str(), value.size());
}

bool BDB::PutDup(const string& key, const string& value) {
	return tcbdbputdup(this->database, key.c_str(), key.size(), value.c_str(), value.size());
}

bool BDB::Add(const string& key, const int value, int& result) {
	result = tcbdbaddint(this->database, key.c_str(), key.length(), value);
	
	if(isnan(result)) {
		return false;
	} else {
		return true;
	}
}

bool BDB::Out(const string& key) {
	return tcbdbout(this->database, key.c_str(), key.size());
}

int BDB::Count(const string& key) {
  return tcbdbvnum(this->database, key.c_str(), key.size());
}

bool BDB::TransactionBegin() {
  return tcbdbtranbegin(this->database);
}

bool BDB::TransactionAbort() {
  return tcbdbtranabort(this->database);
}

bool BDB::TransactionCommit() {
  return tcbdbtrancommit(this->database);
}


/*
 * Returns the last error to occur on the database
 */
string BDB::Error() {
	return string(tcbdberrmsg(tcbdbecode(this->database)));
}

int BDB::ErrorCode() {
	return tcbdbecode(this->database);
}