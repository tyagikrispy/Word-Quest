#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;

class Trienode{
    public:

    //hashmap is used to implement trie , for each character of string inserted in trie the map stores the trienode pointer for the character
    char ch;
    map<char, Trienode* > children;
    string word;
    bool isTerminal;

    //constructor
    Trienode(char ch) {
        this->ch=ch;
        this->word = "";
        this->isTerminal = false;
    }

};

class Trie{
    public:

    Trienode* root;

    Trie() {
        root = new Trienode('\0');
    }

    void insertion(Trienode* root,string word,string &s) {
 
        //if we reach to end of word we mark it in trie by making isTerminal true and also provide given string to word object of root
        if(word.length()==0) {
            root->isTerminal=true;
            root->word = s;
            return;
        }

        //first we insert first character
        char ch = word[0];
    
        //new node child created
        Trienode* child;

        //if we find the charachter ch in the map for root node, we put it in child
        if(root->children.count(ch)!=0) {
            child= root->children[ch];
        }

        //if we dont find character ch in map for root node , we initialize child with ch and put child in the map for ch
        else{
            child = new Trienode(ch);
            root->children[ch]= child;
        }

        //recursive call for inserting remaining characters
        insertion(child,word.substr(1),s);

    }

};

void dfs(vector<vector<char>> &board,Trienode* temp,int i,int j,
         vector<vector<bool>> &visited,set<string> &ans) {

        //checking if i and j are within the dimensions of board
        if (i < 0 || j < 0 || i == board.size() || j == board[0].size()){
            return;
        }

        //checking if the character of this node matches with the character present on board on this position
        if(temp->ch!=board[i][j]) {
            return;
        }

        //if for a word the character has already been visited we cannot visit it again
        if(visited[i][j]) {
            return;
        }

        //this character has been visited
        visited[i][j]=true;

        //if we reach the end of the string we insert our ansswer in set as it can be formed from the board
        if(temp->isTerminal) {
            ans.insert(temp->word);
        }
        
        //iterating through the children of temp node
        for(auto x:temp->children) {

            //8 way dfs call to check in 8 possible directions on board
            dfs(board,x.second,i-1,j-1,visited,ans);
            dfs(board,x.second,i,j-1,visited,ans);
            dfs(board,x.second,i-1,j+1,visited,ans);
            dfs(board,x.second,i+1,j,visited,ans);
            dfs(board,x.second,i+1,j+1,visited,ans);
            dfs(board,x.second,i,j+1,visited,ans);
            dfs(board,x.second,i+1,j-1,visited,ans);
            dfs(board,x.second,i-1,j,visited,ans);

        }
        
        //backtracking after we check for on word
        visited[i][j]=false;

}


void findWords() {
    
    int n,m;
    cin>>n>>m;

    //n->No of rows
    //m->No of coloumns
    
    vector<vector<char>> board(n,vector<char>(m));

    //taking input of characters on board
    for(int i=0;i<n;i++) {

        for(int j=0;j<m;j++) {

            cin>>board[i][j];

        }

    }

    //initializing object t of trie class
    Trie t;

    int no_of_words;
    cin>>no_of_words;

    //taking input of all the words that are to be checked whether they can be formed

    while(no_of_words--) {

        string s;
        cin>>s;
        
        //adding the words to trie
        t.insertion(t.root,s,s);

    }
    
    //initializing a 2d vector to check for if a charcter on board has been visited or not
    vector<vector<bool>> visited(n,vector<bool>(m,false));
 
    //initializing set to store answer as it will remove duplicates and provide unique answer
    set<string> ans;

    for(int i=0;i<n;i++) {

        for(int j=0;j<m;j++) {

            //checking whether the first letter of given word present in trie 
            if(t.root->children.count(board[i][j])!=0) {
                
                //dfs call to check if given word can be formed from board
                dfs(board,t.root->children[board[i][j]],i,j,visited,ans);

            }
        }
    }
 
    //printing all words stored in set
    for(auto i:ans) {
        cout<<i<<endl;
    }

}

int main() {

    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif

    ll TEST_CASES = 1;

    while(TEST_CASES--) {
        findWords();
    }

}