/*
Author:     Bishad Deb Roy Utsha
ID:         2016-3-60-017
email:      royud11@gmail.com
phone:      +8801749315319
linkedin:   linkedin.com/in/bishaddebroy/

*/

#include <bits/stdc++.h>

using namespace std;

class Sender {
    string message;
    int codewordsize;
    char parityType;

    public:
    int getCodeWordSize()
    {
        //calculate the codewordsize
        return codewordsize;
    }
    void setMessage(string message)
    {
        this->message=message;
    }
    void setParityType(char parityType)
    {
        this->parityType=parityType;
    }
    string generateCodeword()
    {
        ///generate the codeword from the message and parityType
        int r=0, m=message.size();
        int i, j;

        while((m+r+1) > pow(2.0, r))
        {
            r++;
        }

        codewordsize=m+r;
        int codeword[m+r]={0};
        for(i=0, j=m-1; i<(m+r); i++)
        {
            int check=ceil(log(i+1)/log(2.0))-floor(log(i+1)/log(2.0));
            ///cout<<check<<endl;
            if(check==0)
            {
                codeword[i]=0;
            }
            else
            {
                if(message[j]=='0')
                    codeword[i]=0;
                else
                    codeword[i]=1;
                j--;
            }
        }
        /*
        ///test
        for(i=0; i<m+r; i++)
            cout<<codeword[i];
        cout<<endl;
        */

        for(i=0; i<r; i++)
        {
            int x=(int) pow(2.0, i);
            for(j=0; j<(m+r); j++)
            {
                if(((j+1>>i)&1)==1)
                {
                    if(x!=j+1)
                        codeword[x-1]=codeword[x-1] ^ codeword[j];

                }
            }
            if(parityType=='o')
            {
                if(codeword[x-1]==0)
                    codeword[x-1]=1;
                else
                    codeword[x-1]=0;
            }
        }
        /*
        ///test
        for(i=0; i<m+r; i++)
            cout<<codeword[i];
        cout<<endl;
        */

        ostringstream os;
        for(i=0; i<(m+r); i++)
        {
            os<<codeword[i];
        }
        string cw(os.str());
        reverse(cw.begin(), cw.end());
        ///cout<<cw<<endl;
        return cw;

    }
};

class Receiver
{
    int codewordsize;
    char parityType;

    public:
    void setCodeWordSize(int codewordsize)
    {
        this->codewordsize=codewordsize;
    }
    void setParityType(char parityType)
    {
        this->parityType=parityType;
    }
    void receiveCodeword(string codeword, int neb=0)
    {
        /*** Check whether the codeword contains an error
        If it does, correct it irrespective of the number of bits in error
        However, more than one bit gets altered, the corrected stream will also be
        erroneous. ***/

        if(neb==0)
        {
            cout<<"For No Change in codeword:"<<endl;
            cout<<"Error Detected in Position: 0"<<endl;
            cout<<"No Error in Codeword"<<endl<<endl;
            return;
        }

        if(neb==2)
        {
            int pos=0;
            for(int i=0; i<2; i++)
            {
                int rnd=rand()%codeword.size();
                pos+=rnd;
                if(codeword[rnd]=='0')
                    codeword[rnd]='1';
                else
                    codeword[rnd]='0';
            }
            cout<<"For Double bit Error:"<<endl;
            cout<<"Error Detected in Position: "<<pos<<endl;
            cout<<"After Correcting, CODEWORD is:"<<endl;
            cout<<codeword<<endl<<endl;
            return;
        }

        int i, j, r=0, n=codeword.size();
        int cw[n]={0};

        while((n+1) > pow(2.0, r))
        {
            r++;
        }
        int m=n-r;
        int erb[r]={0};

        for(i=0; i<n; i++)
        {
            if(codeword[i]=='0')
                cw[i]=0;
            else
                cw[i]=1;
        }

        int k=0;
        for(i=0; i<r; i++)
        {
            int x=(int) pow(2.0, i);
            ///int y=cw[x-1];
            int y=0;
            if(cw[n-x])
                y++;
            for(j=n-1; j>=0; j--)
            {
                if(((j>>i)&1)==1)
                {
                    if(x!=j+1)
                    {
                        if(cw[j])
                            y++;
                    }

                }
            }
            ///cout<<y<<endl;
            if(parityType=='o' && y%2==0)
            {
                erb[k]=1;
            }
            else if(parityType=='e' && y%2==1)
            {
                erb[k]=1;
            }
            k++;
        }

        ostringstream os;
        for(i=0; i<r; i++)
        {
            os<<erb[i];
        }
        string erbit(os.str());
        reverse(erbit.begin(), erbit.end());
        ///cout<<erbit<<endl;

        int errorbit=stoi(erbit, nullptr, 2);

        if(cw[errorbit]==0)
            cw[errorbit]=1;
        else
            cw[errorbit]=0;

        ostringstream os1;
        for(i=0; i<(m+r); i++)
        {
            os1<<cw[i];
        }
        string corrcodeword(os1.str());

        if(neb==1)
        {
            cout<<"For Single bit Error:"<<endl;
            cout<<"Error Detected in Position: "<<n-errorbit<<endl;
            cout<<"After Correcting, CODEWORD is:";
            cout<<corrcodeword<<endl<<endl;

        }

    }
};
    string randomChange(string cw, int num)
    {
        // randomly alter 'num' number of bits in the codeword and return it

        for(int i=0; i<num; i++)
        {
            int rnd=rand()%cw.size();

            if(cw[rnd]=='0')
                cw[rnd]='1';
            else
                cw[rnd]='0';
        }

        return cw;
    }
int main()
{
    Sender sender;
    Receiver receiver;
    string message;
    char parityType; /// 'o' for odd parity, 'e' for even parity
    /// Take the message and parityType as input
    cin>>message>>parityType;

    sender.setMessage(message);
    sender.setParityType(parityType);
    string codeword = sender.generateCodeword();
    string correctCW = codeword;
    string singleErrorCW = randomChange(codeword, 1);
    string doubleErrorCW = randomChange(codeword, 2);
    int codewordsize = sender.getCodeWordSize();

    cout<<"correctCW: "<<correctCW<<endl;
    cout<<"singleErrorCW: "<<singleErrorCW<<endl;
    cout<<"doubleErrorCW: "<<doubleErrorCW<<endl<<endl;


    receiver.setCodeWordSize(codewordsize);
    receiver.setParityType(parityType);
    receiver.receiveCodeword(correctCW);
    receiver.receiveCodeword(singleErrorCW, 1);
    receiver.receiveCodeword(doubleErrorCW, 2);


    return 0;
}
