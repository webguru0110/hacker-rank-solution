#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

vector<long long int> mx;
vector<long long int> mn;

long long int mincomp(int n);
long long int maxcomp(int n);

long long int mnc (int n) {
    //cout<<"mnc "<<n<<endl;
    if (n==1||n==0) return 0;
    if (n==2) return 1;
    int one, two;
    one=(n-1)/2;
    two=n-1-one;
    return (long long int)n-1+mincomp(one)+mincomp(two);
}
long long int mxc (int n) {
    //cout<<"mxc "<<n<<endl;
    if (n==1||n==0) return 0;
    if (n==2) return 1;
    return (long long int)n-1+maxcomp(n-1);
}
long long int mincomp(int n) {
    //cout<<"mincomp "<<n<<endl;
    if (mn.size()<=n) {
        for (int i=mn.size();i<=n;i++) mn.push_back(mnc(i));
    }
    return mn[n];
}
long long int maxcomp(int n) {
    //cout<<"maxcomp "<<n<<" "<<mx.size()<<endl;
    if (mx.size()<=n) {
        //cout<<"maxcomp expanding mx"<<endl;
        for (int i=mx.size();i<=n;i++) mx.push_back(mxc(i));
    }
    //cout<<"maxcomp returning "<<endl;//<<mn[n]<<endl;
    return mx[n];
}

void reverselena(int l,int c,int add, int *arr) {
    //cout<<"rl "<<l<<" "<<c<<" "<<add<<endl;
    if (l==1) {*arr=1+add; return;}
    if (l==2) {*arr= 2+add; *(arr+1)=1+add; return;}
    if (c==maxcomp(l)) {
        //cout<<"rl max"<<endl;
        for (int i=0;i<l;i++) *(arr+i)=l-i+add;
        return;
    }
    if (c==mincomp(l)) {
        //cout<<"rl min"<<endl;
        *arr=add+(l+1)/2;
        reverselena((l-1)/2,mincomp((l-1)/2),add,arr+1);
        reverselena(l-1-(l-1)/2,mincomp(l-1-(l-1)/2),add+(l+1)/2,arr+1+(l-1)/2);
        return;
    }
    int newc=c-(l-1);
    //cout<<"rl here"<<endl;
    for (int i=0;i<l;i++){
        //cout<<"add up to "<<newc<<" "<<maxcomp(l-i-1)<<" + "<<mincomp(i)<<" or "<<maxcomp(i)<<endl;
        if (newc>=mincomp(i)+maxcomp(l-1-i)&&newc<=maxcomp(i)+maxcomp(l-1-i)){
            reverselena(i,newc-maxcomp(l-1-i),add,arr+1);
            //if (one[0]==0) break;
            reverselena(l-1-i,maxcomp(l-1-i),i+1+add,arr+1+i);
            //if (two[0]==0) break;
            *arr=i+1+add;
            return;
        }
    }
    for (int i=0;i<l;i++){
        if (newc>=mincomp(i)+mincomp(l-1-i)&&newc<=maxcomp(i)+mincomp(l-1-i)){
            reverselena(i,newc-mincomp(l-1-i),add,arr+1);
            //if (one[0]==0) break;
            reverselena(l-1-i,mincomp(l-1-i),i+1+add,arr+1+i);
            //if (two[0]==0) break;
            *arr=i+1+add;
            return;
        }
    }

    cout<<"failed for l, c, add "<<l<<" "<<c<<" "<<add<<endl;
    return;
}

int main()
{
    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string lc_temp;
        getline(cin, lc_temp);

        vector<string> lc = split_string(lc_temp);

        int l = stoi(lc[0]);

        int c = stoi(lc[1]);

        // Write Your Code Here
        long long int maxcomparisons=maxcomp(l);
        long long int mincomparisons=mincomp(l);
        //cout<<mincomparisons<<" "<<maxcomparisons<<endl;
        if (c>maxcomparisons||c<mincomparisons) cout<<-1<<endl;
        else {
            //cout<<"here 1"<<endl;
            int* answer=new int[l];
            //cout<<"here 2"<<endl;
            reverselena(l,c,0,answer);
            if (answer[0]==0) cout<<-1<<endl;
            else {
                for (int i=0;i<l;i++) cout<<answer[i]<<" ";
                cout<<endl;
            }
            delete[] answer;
        }
        
    }

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
