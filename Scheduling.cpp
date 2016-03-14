// Author : T.SUBRAMANIAM
// Roll number : 14CO245
// Style of Programming : Object-Oriented
// SIMULATION AND COMPARISON OF PROCESS SCHEDULING ALGORITHMS

#include<bits/stdc++.h>
#include<random>
using namespace std;

class process
{
    int processID;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnAroundTime;
    int priorityValue;
    bool executionDone;

    public :

    void setProcessID(int processID)
    {
        this->processID = processID;
    }

    void setArrivalTime(int arrivalTime)
    {
        this->arrivalTime = arrivalTime;
    }

    void setBurstTime(int burstTime)
    {
        this->burstTime = burstTime;
    }

    void setRemainingTime(int remainingTime)
    {
        this->remainingTime = remainingTime;
    }

    void setWaitingTime(int waitingTime)
    {
        this->waitingTime = waitingTime;
    }

    void setPriorityValue(int priorityValue)
    {
        this->priorityValue = priorityValue;
    }

    void updateWaitingTime(int waitingTime)
    {
        this->waitingTime += waitingTime;
    }

    void updateRemainingTime(int remainingTime)
    {
        this->remainingTime -= remainingTime;
    }

    void setTurnAroundTime(int turnAroundTime)
    {
        this->turnAroundTime = turnAroundTime;
    }
    
    void setExecutionDone(bool executionDone)
    {
    	this->executionDone = executionDone;
	}
	
	int getExecutionDone()
	{
		return executionDone;
	}

    int getProcessID()
    {
        return processID;
    }

    int getPriorityValue()
    {
        return priorityValue;
    }

    int getArrivalTime()
    {
        return arrivalTime;
    }

    int getBurstTime()
    {
        return burstTime;
    }

    int getRemainingTime()
    {
        return remainingTime;
    }

    int getWaitingTime()
    {
        return waitingTime;
    }

    int getTurnAroundTime()
    {
        return turnAroundTime = burstTime + waitingTime;
    }
};

bool compareCriteriaAT(process x, process y)
{
   return x.getArrivalTime() < y.getArrivalTime();
}

struct compareBurstTime
{
    bool operator()(process x, process y)
    {
        return x.getBurstTime() < y.getBurstTime();
    }
};

struct compareRemainingTime
{
    bool operator()(process x, process y)
    {
        return x.getRemainingTime() < y.getRemainingTime();
    }
};

struct comparePriorityValue
{
    bool operator()(process x, process y)
    {
        return x.getPriorityValue() < y.getPriorityValue();
    }
};


void sortProcesses(process p[1001],int numberOfProcesses)
{
    sort(p,p+numberOfProcesses,compareCriteriaAT);
}

void FCFS(process p[1001],int numberOfProcesses)
{
    double totalWaitingTime = 0;
    double totalTurnAroundTime = 0;
    p[0].setWaitingTime(0);
    totalTurnAroundTime += p[0].getTurnAroundTime();
    for(int i = 1; i < numberOfProcesses; i++)
    {
        p[i].setWaitingTime(max(p[i-1].getArrivalTime() + p[i-1].getTurnAroundTime() - p[i].getArrivalTime(),0));
        totalWaitingTime += p[i].getWaitingTime();
        totalTurnAroundTime += p[i].getTurnAroundTime();
    }
    cout<<"Scheduling Algorithm : FCFS\n";
    cout<<"Average Waiting Time : "<<totalWaitingTime/numberOfProcesses<<endl;
    cout<<"Average TurnAround Time : "<<totalTurnAroundTime/numberOfProcesses<<endl;
}

void SJF(process p[1001],int numberOfProcesses)
{
    double totalWaitingTime = 0;
    double totalTurnAroundTime = 0;
    p[0].setWaitingTime(0);

    int timer = 0, i = 0, currentProcessID;
    process currentProcess, readyProcess;
    multiset<process,compareBurstTime> Q;
    multiset<process,compareBurstTime>::iterator it;

    while(p[i].getArrivalTime()==p[0].getArrivalTime())
    {
        Q.insert(p[i]);
        p[i].setWaitingTime(0);
        i++;
    }

    timer = p[0].getArrivalTime();

    while(i <= numberOfProcesses)
    {
        p[i].setWaitingTime(0);
        while(!Q.empty())
        {
            currentProcess = *(Q.begin());
            currentProcessID = currentProcess.getProcessID();
            Q.erase(Q.begin());

            while(p[currentProcessID-1].getRemainingTime() > 0)
            {
                p[currentProcessID-1].updateRemainingTime(1);
                timer++;
                for(it = Q.begin(); it != Q.end(); it++)
                {
                    readyProcess = (*it);
                    p[readyProcess.getProcessID()-1].updateWaitingTime(1);
                }
                if(i >=  numberOfProcesses) continue;
                while(p[i].getArrivalTime() == timer)
                {
                    Q.insert(p[i]);
                    i++;
                    if(i >= numberOfProcesses)break;
                }
            }
        }
        if(i >= numberOfProcesses)break;
        while(timer < p[i].getArrivalTime())
        {
            timer++;
        }
        Q.insert(p[i]);
        i++;
    }

    for(int i = 0; i < numberOfProcesses; i++)
    {
        totalWaitingTime += p[i].getWaitingTime();
        totalTurnAroundTime += p[i].getTurnAroundTime();
    }

    cout<<"Scheduling Algorithm : SJF\n";
    cout<<"Average Waiting Time : "<<totalWaitingTime/numberOfProcesses<<endl;
    cout<<"Average TurnAround Time : "<<totalTurnAroundTime/numberOfProcesses<<endl;
}

void SRTF(process p[1001],int numberOfProcesses)
{
    double totalWaitingTime = 0;
    double totalTurnAroundTime = 0;
    p[0].setWaitingTime(0);

    int timer = 0, i = 0, currentProcessID;
    process currentProcess, readyProcess;
    multiset<process,compareRemainingTime> Q;
    multiset<process,compareRemainingTime>::iterator it;

    while(p[i].getArrivalTime()==p[0].getArrivalTime())
    {
        Q.insert(p[i]);
        p[i].setWaitingTime(0);
        i++;
    }

    timer = p[0].getArrivalTime();

    while(i <= numberOfProcesses)
    {
        p[i].setWaitingTime(0);
        while(!Q.empty())
        {
            currentProcess = *(Q.begin());
            currentProcessID = currentProcess.getProcessID();
            Q.erase(Q.begin());

            while(p[currentProcessID-1].getRemainingTime() > 0)
            {
                p[currentProcessID-1].updateRemainingTime(1);
                timer++;
                for(it = Q.begin(); it != Q.end(); it++)
                {
                    readyProcess = (*it);
					p[readyProcess.getProcessID()-1].updateWaitingTime(1);
                }
                if(i >=  numberOfProcesses) continue;
                while(p[i].getArrivalTime() == timer)
                {
                    if(p[i].getRemainingTime() < p[currentProcessID-1].getRemainingTime())
                    {
                        Q.insert(p[currentProcessID-1]);
                        currentProcessID = i + 1;
                    }
                    else
                    {
                        Q.insert(p[i]);
                    }
                    i++;
                    if(i >= numberOfProcesses)break;
                }
            }
        }
        if(i >= numberOfProcesses)break;
        while(timer < p[i].getArrivalTime())
        {
            timer++;
        }
        Q.insert(p[i]);
        i++;
    }

    for(int i = 0; i < numberOfProcesses; i++)
    {
        totalWaitingTime += p[i].getWaitingTime();
        totalTurnAroundTime += p[i].getTurnAroundTime();
    }

    cout<<"Scheduling Algorithm : SRTF\n";
    cout<<"Average Waiting Time : "<<totalWaitingTime/numberOfProcesses<<endl;
    cout<<"Average TurnAround Time : "<<totalTurnAroundTime/numberOfProcesses<<endl;
}

void roundRobin(process p[1001],int numberOfProcesses, int timeQuantum)
{
    double totalWaitingTime = 0;
    double totalTurnAroundTime = 0;
    p[0].setWaitingTime(0);
    process currentProcess,readyProcess;
    vector<process> Q;
    vector<process>::iterator it,itCurrent;
    int i = 0, counter = 0;
    bool flag = 0;

    while(p[i].getArrivalTime() == p[0].getArrivalTime())
    {
        Q.push_back(p[i]);
        i++;
    }
	
	itCurrent = Q.begin();
	
    int timer = p[0].getArrivalTime();
    int currentProcessID;

    while(1)
    {   	
        	if(itCurrent == Q.end())
        	{
        		itCurrent = Q.begin();
        		readyProcess = *itCurrent;
        		while(readyProcess.getExecutionDone()==1)
				{
					itCurrent++;
					readyProcess = *itCurrent;
					if(itCurrent == Q.end())break;
				}
			}
			
			int check = 0;

			for(it = Q.begin(); it != Q.end(); it++)
			{
				readyProcess = (*it);
				if(p[readyProcess.getProcessID()-1].getExecutionDone()==0)break;
				check++;
			}
			
			if(it==Q.end()&&check==numberOfProcesses)break;
			
			else if(it==Q.end())
			{
				if(i >= numberOfProcesses)break;
     	   		while(timer < p[i].getArrivalTime())
        		{
            		timer++;
        		}
        		Q.push_back(p[i]);
        		i++;
        		itCurrent = Q.begin();
        		while(readyProcess.getProcessID() != p[i-1].getProcessID()) 
				{
						itCurrent++;
						readyProcess = (*itCurrent);
				}
    		}
			
            currentProcess = (*itCurrent);
            currentProcessID = currentProcess.getProcessID();
            flag = 0;
            for(counter = 0; counter < timeQuantum; counter++)
            {	
            	while(i < numberOfProcesses && p[i].getArrivalTime() == timer)
                {
                    Q.push_back(p[i]);
                    i++;
                    itCurrent = Q.begin();
                    readyProcess = (*itCurrent);
                    while(readyProcess.getProcessID() != currentProcessID) 
					{
						itCurrent++;
						readyProcess = (*itCurrent);
					}
                }
                p[currentProcessID-1].updateRemainingTime(1);
                for(it = Q.begin(); it != Q.end(); it++)
                {
                    readyProcess = (*it);
                    if(readyProcess.getProcessID() == currentProcessID || p[readyProcess.getProcessID()-1].getExecutionDone() == 1)continue;
                    p[readyProcess.getProcessID()-1].updateWaitingTime(1);
                }
                timer++;
                if(p[currentProcessID-1].getRemainingTime() == 0)
                {
                	p[currentProcessID-1].setExecutionDone(1);
                    break;
            	}
            }
            itCurrent++;
            if(itCurrent != Q.end()) readyProcess = *itCurrent;
            while(itCurrent!=Q.end() && (p[readyProcess.getProcessID()-1].getExecutionDone()==1))
				{
					itCurrent++;
					readyProcess = *itCurrent;
				}
    }
    
    for(int i = 0; i < numberOfProcesses; i++)
    {
        totalWaitingTime += p[i].getWaitingTime();
        totalTurnAroundTime += p[i].getTurnAroundTime();
    }

    cout<<"Scheduling Algorithm : RoundRobin\n";
    cout<<"Average Waiting Time : "<<totalWaitingTime/numberOfProcesses<<endl;
    cout<<"Average TurnAround Time : "<<totalTurnAroundTime/numberOfProcesses<<endl;
}

void priorityPreemptive(process p[1001],int numberOfProcesses)
{
    double totalWaitingTime = 0;
    double totalTurnAroundTime = 0;
    p[0].setWaitingTime(0);

    int timer = 0, i = 0, currentProcessID;
    process currentProcess,readyProcess;
    multiset<process,comparePriorityValue> Q;
    multiset<process,comparePriorityValue>::iterator it;

    while(p[i].getArrivalTime()==p[0].getArrivalTime())
    {
        Q.insert(p[i]);
        i++;
    }

    timer = p[0].getArrivalTime();

    while(i <= numberOfProcesses)
    {
        p[i].setWaitingTime(0);
        while(!Q.empty())
        {
            currentProcess = *(Q.begin());
            currentProcessID = currentProcess.getProcessID();
            Q.erase(Q.begin());

            while(p[currentProcessID-1].getRemainingTime() > 0)
            {
                p[currentProcessID-1].updateRemainingTime(1);
                timer++;
                for(it = Q.begin(); it != Q.end(); it++)
                {
                    readyProcess = (*it);
                    p[readyProcess.getProcessID()-1].updateWaitingTime(1);
                }
                if(i >=  numberOfProcesses) continue;
                while(p[i].getArrivalTime() == timer)
                {
                    if(p[i].getPriorityValue() < p[currentProcessID-1].getPriorityValue())
                    {
                        Q.insert(p[currentProcessID-1]);
                        currentProcessID = i + 1;
                    }
                    else
                    {
                        Q.insert(p[i]);
                    }
                    i++;
                }
            }
        }
        if(i >= numberOfProcesses)break;
        while(timer < p[i].getArrivalTime())
        {
            timer++;
        }
        Q.insert(p[i]);
        i++;
    }

    for(int i = 0; i < numberOfProcesses; i++)
    {
        totalWaitingTime += p[i].getWaitingTime();
        totalTurnAroundTime += p[i].getTurnAroundTime();
    }

    cout<<"Scheduling Algorithm : Preemptive Priority Scheduling\n";
    cout<<"Average Waiting Time : "<<totalWaitingTime/numberOfProcesses<<endl;
    cout<<"Average TurnAround Time : "<<totalTurnAroundTime/numberOfProcesses<<endl;
}

void priorityNonPreemptive(process p[1001],int numberOfProcesses)
{
    double totalWaitingTime = 0;
    double totalTurnAroundTime = 0;
    p[0].setWaitingTime(0);

    int timer = 0, i = 0, currentProcessID;
    process currentProcess, readyProcess;
    multiset<process,comparePriorityValue> Q;
    multiset<process,comparePriorityValue>::iterator it;

    while(p[i].getArrivalTime()==p[0].getArrivalTime())
    {
        Q.insert(p[i]);
        p[i].setWaitingTime(0);
        i++;
    }

    timer = p[0].getArrivalTime();

    while(i <= numberOfProcesses)
    {
        p[i].setWaitingTime(0);
        while(!Q.empty())
        {
            currentProcess = *(Q.begin());
            currentProcessID = currentProcess.getProcessID();
            Q.erase(Q.begin());

            while(p[currentProcessID-1].getRemainingTime() > 0)
            {
                p[currentProcessID-1].updateRemainingTime(1);
                timer++;
                for(it = Q.begin(); it != Q.end(); it++)
                {
                    readyProcess = (*it);
                    p[readyProcess.getProcessID()-1].updateWaitingTime(1);
                }
                if(i >=  numberOfProcesses) continue;
                while(p[i].getArrivalTime() == timer)
                {
                    Q.insert(p[i]);
                    i++;
                    if(i >= numberOfProcesses)break;
                }
            }
        }
        if(i >= numberOfProcesses)break;
        while(timer < p[i].getArrivalTime())
        {
            timer++;
        }
        Q.insert(p[i]);
        i++;
    }

    for(int i = 0; i < numberOfProcesses; i++)
    {
        totalWaitingTime += p[i].getWaitingTime();
        totalTurnAroundTime += p[i].getTurnAroundTime();
    }

    cout<<"Scheduling Algorithm : NonPreemptive Priority Scheduling\n";
    cout<<"Average Waiting Time : "<<totalWaitingTime/numberOfProcesses<<endl;
    cout<<"Average TurnAround Time : "<<totalTurnAroundTime/numberOfProcesses<<endl;
}

void cleanUp(process p[1001],int numberOfProcesses)
{
    for(int i = 0; i < numberOfProcesses; i++)
    {
        p[i].setWaitingTime(0);
        p[i].setTurnAroundTime(0);
        p[i].setRemainingTime(p[i].getBurstTime());
        p[i].setExecutionDone(0);
    }
}

int main()
{
    int numberOfProcesses;
    int timeQuantum;
    process p[1001];
    bool ok = 0;

    random_device r;
    seed_seq seed{r(),r(),r(),r(),r(),r()};
    mt19937 eng{seed};
    uniform_int_distribution<> range(1,100),rangePriority(1,20);

    while(!ok)
    {
        cout<<"Enter number of processes (10-1000) : ";
        cin>>numberOfProcesses;
        ok = 1;
        if(numberOfProcesses<4||numberOfProcesses>1000)
        {
            ok = 0;
            cout<<"Check the accepted range again!"<<endl;
        }
    }

    ok = 0;
    while(!ok)
    {
        cout<<"Enter timeQuantum value (10-20) : ";
        cin>>timeQuantum;
        ok = 1;
        if(timeQuantum<10||timeQuantum>20)
        {
            ok = 0;
            cout<<"Check the accepted range again!"<<endl;
        }
    }

    for(int i = 0; i < numberOfProcesses; i++)
    {
        p[i].setArrivalTime(range(eng));
        p[i].setBurstTime(range(eng));
        p[i].setPriorityValue(rangePriority(eng));

    }

    sortProcesses(p,numberOfProcesses);
	cout<<endl;

	cout<<"ProcessID   ArrivalTime     BurstTime          PriorityValue\n";

    for(int i = 0; i < numberOfProcesses; i++)
    {
        p[i].setProcessID(i+1);
        cout<<i+1<<"            "<<p[i].getArrivalTime()<<"                 "<<p[i].getBurstTime()<<"                 "<<p[i].getPriorityValue()<<endl;
    }

	cout<<endl<<endl;
	cout<<"--------------------------------------------------------------------------------------------------\n";

    FCFS(p,numberOfProcesses);
    cout<<endl;
    cout<<"ProcessID   WaitingTime     TurnAroundTime\n";
	for(int i = 0; i < numberOfProcesses; i++)
    {
        cout<<i+1<<"            "<<p[i].getWaitingTime()<<"                 "<<p[i].getTurnAroundTime()<<endl;
    }
	cleanUp(p,numberOfProcesses);
	cout<<endl<<endl;
	cout<<"--------------------------------------------------------------------------------------------------\n";


    SJF(p,numberOfProcesses);
    cout<<endl;
    cout<<"ProcessID   WaitingTime     TurnAroundTime\n";
	for(int i = 0; i < numberOfProcesses; i++)
    {
        cout<<i+1<<"            "<<p[i].getWaitingTime()<<"                 "<<p[i].getTurnAroundTime()<<endl;
    }
    cleanUp(p,numberOfProcesses);
    cout<<endl<<endl;
    cout<<"--------------------------------------------------------------------------------------------------\n";

    SRTF(p,numberOfProcesses);
    cout<<endl;
    cout<<"ProcessID   WaitingTime     TurnAroundTime\n";
	for(int i = 0; i < numberOfProcesses; i++)
    {
        cout<<i+1<<"            "<<p[i].getWaitingTime()<<"                 "<<p[i].getTurnAroundTime()<<endl;
    }
    cleanUp(p,numberOfProcesses);
    cout<<endl<<endl;
    cout<<"--------------------------------------------------------------------------------------------------\n";

    roundRobin(p,numberOfProcesses,timeQuantum);
    cout<<endl;
	cout<<"ProcessID   WaitingTime     TurnAroundTime\n";
	for(int i = 0; i < numberOfProcesses; i++)
    {
        cout<<i+1<<"            "<<p[i].getWaitingTime()<<"                 "<<p[i].getTurnAroundTime()<<endl;
    }
    cleanUp(p,numberOfProcesses);
    cout<<endl<<endl;
    cout<<"--------------------------------------------------------------------------------------------------\n";


    priorityPreemptive(p,numberOfProcesses);
    cout<<endl;
    cout<<"ProcessID   WaitingTime     TurnAroundTime\n";
	for(int i = 0; i < numberOfProcesses; i++)
    {
        cout<<i+1<<"            "<<p[i].getWaitingTime()<<"                 "<<p[i].getTurnAroundTime()<<endl;
    }
    cleanUp(p,numberOfProcesses);
    cout<<endl<<endl;
    cout<<"--------------------------------------------------------------------------------------------------\n";

    priorityNonPreemptive(p,numberOfProcesses);
    cout<<endl;
    cout<<"ProcessID   WaitingTime     TurnAroundTime\n";
	for(int i = 0; i < numberOfProcesses; i++)
    {
        cout<<i+1<<"            "<<p[i].getWaitingTime()<<"                 "<<p[i].getTurnAroundTime()<<endl;
    }
    cleanUp(p,numberOfProcesses);
    cout<<endl<<endl;
    cout<<"--------------------------------------------------------------------------------------------------\n";

    return 0;
}


