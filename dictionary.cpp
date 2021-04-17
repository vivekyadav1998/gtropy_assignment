#include <bits/stdc++.h>
using namespace std;

class dictData{
    public:
        char wordChar;
        vector<dictData*> childCharPtr; 
        bool isTerminal;              
    
        dictData(char c){
            wordChar = c;
            childCharPtr.resize(26,NULL);
            isTerminal = false;
        }
        friend class dictionary;
};

class dictionary{    
    public:
        dictData* parentNode;
    
        dictionary(){
            parentNode = new dictData('\0');     ////root node
        }
        void buildDict(string inputWord){
            dictData* iterator = parentNode;
            for(int i=0;i<inputWord.size();i++){
                int index = inputWord[i]-'a';
                if(iterator->childCharPtr[index] == NULL){
                    dictData* newDictData = new dictData(inputWord[i]);
                    iterator->childCharPtr[index] = newDictData;
                    iterator = newDictData;
                }
                else iterator = iterator->childCharPtr[index];
            }
            iterator->isTerminal = true;
            return;
        }

        void printAllSuggestions(dictData* iterator,string outputWord){
            if(iterator->isTerminal){
                cout<<outputWord<<endl;
            }
            for(int i=0;i<26;i++){
                if(iterator->childCharPtr[i]){
                    outputWord.push_back(i+'a');
                    printAllSuggestions(iterator->childCharPtr[i],outputWord);
                    outputWord.pop_back();
                }
            }
            return;
        }

        int findSuggestion(string inputQuery){
            dictData* iterator = parentNode;
            for(int i=0;i<inputQuery.size();i++){
                int index = inputQuery[i]-'a';
                if(!iterator->childCharPtr[index]){
                    return -1;
                }
                else iterator = iterator->childCharPtr[index];
            }
             if(iterator->isTerminal){                              //if we got the same word
                cout<<"Below are the relevant word: \n";
                cout<<inputQuery<<endl;
            }
            else{                                                   ////all prediction word
                cout<<"Below are the relevant words: \n";
             printAllSuggestions(iterator,inputQuery);
         }
            return 1;
        }
};

int main() {
    vector<string>input_words={
"aah","aahed","aahing","aahs","aardvark","aardvarks","aardwolf""ab","abaci","aback","abacus","abacuses","abaft","abalone","abalones",
"abandon",
"abandoned",
"abandonedly",
"abandonee",
"abandoner",
"abandoners"
"abandoning",
"abandonment",
"abandonments",
"abandons",
"abase",
"abased",
"abasedly",
"abasement",
"abaser",
"abasers",
"abases",
"abash",
"abashed",
"abashedly",
"abashes",
"abashing",
"abashment",
"abashments",
"abasing",
"abatable",
"abate",
"abated",
"abatement",
"abatements",
"abater",
"abaters",
"abates",
"abating",
"abatis",
"abatises",
"abator"
    };
    dictionary d;                         /////creating object

    for(auto x:input_words){
                                ///word in dictionary
        
          d.buildDict(x);
    }
    string s2;                             //word for search
    cin>>s2;
    int result=d.findSuggestion(s2);
    if(result == -1) cout<<"No suggestions :)"<<endl;
    return 0;
}
