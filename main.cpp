#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>

using namespace std;

class Node{
    public:
    char symb;
    bool finish;
    vector <Node*> child;
    Node (){
        symb = '/';
        finish = false;
        child = vector<Node*> {};
    }
    Node (char c, bool fin, vector<Node*> subchild): symb{c}, finish{fin}, child{subchild}{}
};

vector <string> find_appeals(string s){
    vector <string> res;
    bool flag = false;
    string tmp = "";
    int space = 0;
    long long m = 0, c = 0;
    for (size_t i = 0; i < s.size(); ++i){
        ++c;
        if (s[i] == ',' && !flag){
            flag = true;
        }   else if (s[i] == ',' && flag){
            ++m;
            res.push_back(tmp);
            tmp = "";
        }   else if (flag && s[i] != ' '){
            tmp += s[i];

        }   else if (flag && s[i] == ' ' && space < 1){
            ++space;
        }  else if (flag && s[i] == ' ' && space == 1){
            space = 0;
            tmp = "";
            flag = false;
        }
    }
    cout << "comp: "<< c << " move: "<< m << '\n';
    return res;
}
int max_substring(string a, string b){
    vector <int> arr_a;
    arr_a.resize(a.size(), 0);
    long long c = 0, m = 0;
    for (int i = 0; i < a.size(); ++i){
        for (int j = 0; j < a.size() && j < i ; ++j){
            if (a.substr(0, j) == a.substr(i - j + 1,j)){
                arr_a[i] = (arr_a[i] < j)? j : arr_a[i];
                ++m;
            }
            ++c;

        }
    }
    int i = 0, j = 0;
    int max_value = 0;
    while (i != b.size() && j != a.size()){
        if (b[i] == a[j]){
            ++i;
            ++j;
            ++c;
            max_value = (max_value < j) ? j : max_value;
            ++m;
        }
        else if (b[i] != a[j]){
            c += 2;
            if (j > 0 ){
                j = arr_a[j - 1];
                ++m;
                ++c;
            }
            else{
                ++i;
            }
        }
    }
    cout << "comp: " << c << " move: " << m << endl;
    return max_value;
}
Node* create_dict(string a){
    Node* res = new Node();
    Node* tmp = res;
    stringstream stream(a);
    string word = "";
    long long c = 0, m = 0;
    while (getline(stream, word)){
        tmp = res;
        for (int i = 0; i < word.size(); ++i){
            bool flag = false;
            for (int j = 0; j < tmp->child.size(); ++j){
                ++c;
                if (tmp->child[j]->symb == word[i]){
                    tmp = tmp->child[j];
                    ++m;
                    flag = true;
                    break;
                }
            }
            ++c;
            if (!flag){
                Node* new_symb;
                ++c;
                if (i == word.size() - 1){
                    new_symb = new Node{word[i], true, vector<Node*> {}};
                }
                else new_symb = new Node{word[i], false, vector<Node*> {}};
                tmp->child.push_back(new_symb);
                ++m;
                tmp = tmp->child[tmp->child.size() - 1];
            }
        }
    }
    cout << "comp: " << c << " move: "<< m << endl;
    return res;
}
bool check_word(string word, Node* root){
    for (int i = 0; i < word.size(); ++i){
        bool flag = false;
        for (int j = 0; j < root->child.size(); ++j){
            if (root->child[j]->symb == word[i]){
                root = root->child[j];
                flag = true;
                break;
            }
        }
        if (!flag)  return false;
    }
    if (!root->finish)  return false;
    return true;
}

int main(){
    for (int n = 100; n <= 1000000; n *= 10){
        ifstream fin(to_string(n)+"_2.txt");
        //ifstream fin_2("input.txt");
        string s;//, s_2;
        cout << endl;
        getline(fin, s);
        //getline(fin_2, s_2);
        //fin >> s;
        auto start = std::chrono::steady_clock::now();
        //vector <string> r = find_appeals(s);
        //int p = max_substring(s_2, s);
        create_dict(s);
        auto end = std::chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end-start;
        cout << "elapsed time for" << n << ": " << elapsed_seconds.count() << "s\n";
        //cout << p;
        cout << endl;
    }

    
    /*
    vector <string> appeals;

    
    cout << "Out appeals: \n";
    for (int i = 0; i < appeals.size(); ++i){
        
        cout << appeals[i];
        if (i < appeals.size() - 1) cout << ", ";
        else    cout << " ";
    }
    */
    //cout << max_substring("abcab", "abcsdcndsagbcabcajnfd");
    //Node* t = create_dict("asd");
    //cout << check_word("asd", t);
    return 0;
}