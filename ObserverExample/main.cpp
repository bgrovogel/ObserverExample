#include <iostream>
#include <vector>
using namespace std;

class Subject {
    
    vector < class Observer * > views; //Coupled only to "interface"
    int value;
  public:
    void attach(Observer *obs) {
        views.push_back(obs);
    }
    void setValue(int val) {
        value = val;
        notify();
    }
    int getValue() {
        return value;
    }
    void notify();
};

class Observer {
    // 2. "dependent" functionality
    Subject *modulus;
    int deno;
  public:
    Observer(Subject *mod, int div) {
        modulus = mod;
        deno = div;
        // 4. Obs register themselves with the Subj
        modulus->attach(this);
    }
    virtual void update() = 0;
  protected:
    Subject *getSubject() {
        return modulus;
    }
    int getDivisor() {
        return deno;
    }
};

void Subject::notify() {
  // 5. Publ broadcasts
  for (int i = 0; i < views.size(); i++)
    views[i]->update();
}

class DivObserver: public Observer {
  public:
    DivObserver(Subject *mod, int div): Observer(mod, div){}
    void update() {
        // 6. "Pull" information of interest
        int v = getSubject()->getValue(), d = getDivisor();
        cout << v << " divided by " << d << " is " << v / d << '\n';
    }
};

class ModObserver: public Observer {
  public:
    ModObserver(Subject *mod, int div): Observer(mod, div){}
    void update() {
        int v = getSubject()->getValue(), d = getDivisor();
        cout << v << " mod " << d << " is " << v % d << '\n';
    }
};

int main() {
  Subject subj;
  DivObserver divObs1(&subj, 50); // Client configures the number
  DivObserver divObs2(&subj, 5); //  type of Obs
  ModObserver modObs3(&subj, 25);
  subj.setValue(2020);
}