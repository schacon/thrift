// Copyright (c) 2006- Facebook
// Distributed under the Thrift Software License
//
// See accompanying file LICENSE or visit the Thrift site at:
// http://developers.facebook.com/thrift/

#include "FacebookBase.h"

using namespace facebook::fb303;
using facebook::thrift::concurrency::Guard;

FacebookBase::FacebookBase(std::string name, get_static_limref_ptr reflect_lim) :
  name_(name) {
  aliveSince_ = (int64_t) time(NULL);
  if (reflect_lim) {
    reflect_lim(reflection_limited_);
  }
}

inline void FacebookBase::getName(std::string& _return) {
  _return = name_;
}

void FacebookBase::setOption(const std::string& key, const std::string& value) {
  Guard g(optionsLock_);
  options_[key] = value;
}

void FacebookBase::getOption(std::string& _return, const std::string& key) {
  Guard g(optionsLock_);
  _return = options_[key];
}

void FacebookBase::getOptions(std::map<std::string, std::string> & _return) {
  Guard g(optionsLock_);
  _return = options_;
}

int64_t FacebookBase::incrementCounter(const std::string& key, int64_t amount) {
  counters_.acquireRead();

  // if we didn't find the key, we need to write lock the whole map to create it
  ReadWriteCounterMap::iterator it = counters_.find(key);
  if (it == counters_.end()) {
    counters_.release();
    counters_.acquireWrite();

    // we need to check again to make sure someone didn't create this key
    // already while we released the lock
    it = counters_.find(key);
    if(it == counters_.end()){
      counters_[key].value = amount;
      counters_.release();
      return amount;
    }
  }

  it->second.acquireWrite();
  int64_t count = it->second.value + amount;
  it->second.value = count;
  it->second.release();
  counters_.release();
  return count;
}

int64_t FacebookBase::setCounter(const std::string& key, int64_t value) {
  counters_.acquireRead();

  // if we didn't find the key, we need to write lock the whole map to create it
  ReadWriteCounterMap::iterator it = counters_.find(key);
  if (it == counters_.end()) {
    counters_.release();
    counters_.acquireWrite();
    counters_[key].value = value;
    counters_.release();
    return value;
  }

  it->second.acquireWrite();
  it->second.value = value;
  it->second.release();
  counters_.release();
  return value;
}

void FacebookBase::getCounters(std::map<std::string, int64_t>& _return) {
  // we need to lock the whole thing and actually build the map since we don't
  // want our read/write structure to go over the wire
  counters_.acquireRead();
  for(ReadWriteCounterMap::iterator it = counters_.begin();
      it != counters_.end(); it++)
  {
    _return[it->first] = it->second.value;
  }
  counters_.release();
}

int64_t FacebookBase::getCounter(const std::string& key) {
  int64_t rv = 0;
  counters_.acquireRead();
  ReadWriteCounterMap::iterator it = counters_.find(key);
  if (it != counters_.end()) {
    it->second.acquireRead();
    rv = it->second.value;
    it->second.release();
  }
  counters_.release();
  return rv;
}

inline int64_t FacebookBase::aliveSince() {
  return aliveSince_;
}

