#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<bool> keys(512);

  cout << "before setting anything..." << endl;
  cout << "key 10: " << keys[10] << endl;
  cout << "key 35: " << keys[35] << endl;
  cout << "key 160: " << keys[160] << endl;

  cout << "setting 35, 60, 90 to true..." << endl;
  keys[35] = true;
  keys[60] = true;
  keys[90] = true;
  cout << "key 10: " << keys[10] << endl;
  cout << "key 35: " << keys[35] << endl;
  cout << "key 160: " << keys[160] << endl;
}
