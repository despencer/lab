#include <iostream>
#include <map>

class Key
{
public:
  int k;
public:
  Key(int _k) { k = _k; std::cout << "Key Constructor " << k << "\n"; }
  virtual ~Key() { std::cout << "Key Destructor " << k << "\n"; }
};

class Test
{
public:
  int a;
public:
  Test(int _a) { a = _a; std::cout << "Test Constructor " << a << "\n"; }
  virtual ~Test() { std::cout << "Test Destructor " << a << "\n"; }
};

Test* find(std::map<Key*,Test*>& lookup, Key* key)
{
 if(auto search = lookup.find(key); search != lookup.end())
    {
    std::cout << "Found " << search->second->a << " for key " << key->k << "\n";
    return search->second;
    }
 std::cout << "Absent for key " << key->k << "\n";
 return NULL;
}

void maptest(void)
{
 std::map<Key*,Test*> lookup;
 Key* key1 = new Key(1);
 lookup.insert(std::make_pair(key1, new Test(1)));
 lookup.insert(std::make_pair(new Key(2), new Test(2)));

 Key* key3 = new Key(3);
 find(lookup, key3);
 Key* key4 = new Key(1);
 find(lookup, key4);
 find(lookup, key1);

 std::cout << "size " << lookup.size() << "\n";

 for(auto& m : lookup)
   { delete m.first; delete m.second; }
 lookup.clear();
 delete key3; delete key4;
}

int main(int argc, const char* argv[])
{
 maptest();
}