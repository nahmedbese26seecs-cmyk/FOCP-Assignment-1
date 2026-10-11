#include <iostream>
#include <iomanip>
using namespace std;

int main() {
        int defered_requests=0;
        int success_requests=0;
        
        int trucks;
        int packs;

    cout<<"Press 1 to use full resources (5 trucks and 120 supply packs)"<<endl;
    cout<<"Press 2 to use partial resources (2 trucks and 70 supply packs)"<<endl;
    
    int choice;
    cin>>choice;
        
    while(choice<1 || choice >2){
            cout<<"invalid commmand, press 1 or 2"<<endl;
            cin>>choice;
    }    
        
    switch(choice){
            case 1: 
                trucks = 5;
                packs = 120;
                    break;     
            case 2: 
                    trucks = 2;
                    packs = 70;
                    break;
    }
    

    //Taking n requests from the user
    cout << "Enter the amount of requests to be made:" << endl;
    
    int r;
    cin >> r;

    for (int i = 1; i <= r; i++) {
        cout << "Taking request NO. " << i << endl;
        cout << "current resoures :" << endl;
        cout << "trucks: " << trucks << endl;
        cout << "supply packs: " << packs << endl;

        // Taking inputs for the variables from the user
        cout << "enter damage : H for high , m for medium , l for low " << endl;
       
        char damage;
        cin >> damage;
       
        while (damage != 'h' && damage != 'H' && damage != 'm' && damage != 'M' && damage != 'L' && damage != 'l') {
            cout << "wrong command" << endl;
            cin >> damage;
        }

        cout << "enter the amount of families effected (10 to 200)" << endl;
       
        int fams;
        cin >> fams;
       
        while (fams < 10 || fams>200) {
            cout << "invalid command (enter between 10 and 200)" << endl;
            cin >> fams;
        }

        cout << "Access route condition : (o for open and D for damamged)" << endl;
       
        char access_route;
        cin >> access_route;
       
        while (access_route != 'O' && access_route != 'o' && access_route != 'd' && access_route != 'D') {
            cout << "wrong command" << endl;
            cin >> access_route;
        }

        cout << "Flood warning? (Y for yes and N for no)" << endl;
       
        char flood_warning;
        cin >> flood_warning;
       
        while (flood_warning != 'y' && flood_warning != 'Y' && flood_warning != 'n' && flood_warning != 'N') {
            cout << "wrong command" << endl;
            cin >> flood_warning;
        }

        cout << "medical need? (Y for yes and N for no)" << endl;
       
        char med_need;
        cin >> med_need;
       
        while (med_need != 'y' && med_need != 'Y' && med_need != 'n' && med_need != 'N') {
            cout << "wrong command" << endl;
            cin >> med_need;
        }

        cout << "previous aid received? (Y for yes and N for no)" << endl;
       
        char prev_aid;
        cin >> prev_aid;
       
        while (prev_aid != 'y' && prev_aid != 'Y' && prev_aid != 'n' && prev_aid != 'N') {
            cout << "wrong command" << endl;
            cin >> prev_aid;
        }

        cout << endl;

        //calculating scores:
        int dmg_score;
        if (damage == 'H' || damage == 'h') {
            dmg_score = 30;
        }
        else if (damage == 'm' || damage == 'M') {
            dmg_score = 20;
        }
        else {
            dmg_score = 10;
        }

       
        int fam_score;
        if (fams >= 10 && fams <= 90) {
            fam_score = 10;
        }
        else if (fams >= 90 && fams <= 150) {
            fam_score = 20;
        }
        else {
            fam_score = 30;
        }

       
        int route_score;
        if (access_route == 'o' || access_route == 'O') {
            route_score = 10;
        }
        else {
            route_score = -5;
        }

       
        int flood_score;
        if (flood_warning == 'y' || flood_warning == 'Y') {
            flood_score = 10;
        }
        else {
            flood_score = 0;
        }

       
        int med_score;
        if (med_need == 'y' || med_need == 'Y') {
            med_score = 15;
        }
        else {
            med_score = 0;
        }

       
        int prev_aid_score=0;
        if (prev_aid == 'y' || prev_aid == 'Y') {
            prev_aid_score -= 5;
        }
        else {
            prev_aid_score = 5;
        }

        //Displaying Inputs:
        cout << left << "inputs:" << right << setw(35) << "Values:"<<right<<setw(20)<<"Scores:" << endl;

        cout << left << setw(20) << "Damage Level" << right << setw(20) << damage<<right<<setw(20)<<dmg_score << endl;
        cout << left << setw(20) << "Families effectd:" << right << setw(20) << fams<<right<<setw(20)<<fam_score << endl;
        cout << left << setw(20) << "Access route" << right << setw(10) << access_route << " (O= open, D=damaged)" <<right<<setw(9)<<route_score<< endl;
        cout << left << setw(20) << "flood Warning" << right << setw(10) << flood_warning << " (Y=yes, N=No)" <<right<<setw(16)<<flood_score<< endl;
        cout << left << setw(20) << "medical need" << right << setw(10) << med_need << " (Y=yes, N=No)"<<right<<setw(16)<<med_score << endl;
        cout << left << setw(20) << "previous aid" << right << setw(10) << prev_aid << " (Y=yes, N=No)" <<right<<setw(16)<<prev_aid_score<< endl;
        cout << endl;

       
        int total_score = dmg_score + route_score + fam_score + flood_score + med_score + prev_aid_score;
        cout << "the total score is: " << total_score << endl;
        cout << endl;


        //Taking acton:
        if(total_score>75){
            if(trucks>=2 && packs>=50){
                cout<<"sending full relief : 2 trucks and 50 supply packs "<<endl;
                trucks-=2;
                packs-=50;
                success_requests+=1;
            }
            else if(trucks >=1 && packs >=30){
                cout<<"less resources for full relief : sending standard relief : 1 trucks and 30 supply packs "<<endl;
                trucks-=1;
                packs-=30;
                success_requests+=1;
            }
            else if(trucks >=1 && packs >=10){
                cout<<"less resources for full and standard : sending emergency kit only : 1 trucks and 10 supply packs "<<endl;
                trucks-=1;
                packs-=10;
                success_requests+=1;
            }
            else{
                cout<<"request deffered because of insufficient resources"<<endl;
                defered_requests+=1;
            }
        }
        
        
        if(total_score>50 && total_score<=75){
            if(trucks>=1 && packs>=30){
                cout<<"sending standard relief : 2 trucks and 50 supply packs "<<endl;
                trucks-=2;
                packs-=50;
                success_requests+=1;
            }
            else if(trucks >=1 && packs >=10){
                cout<<"less resources for standard relief : sending emergency kit only : 1 trucks and 10 supply packs "<<endl;
                trucks-=1;
                packs-=10;
                success_requests+=1;
            }
            else{
                cout<<"request deffered because of insufficient resources"<<endl;
                defered_requests+=1;
            }
        }
        
        
        if(total_score>25 && total_score<=50){
            if(trucks >=1 && packs >=10){
                cout<<"sending emergency kit only : 1 trucks and 10 supply packs "<<endl;
                trucks-=1;
                packs-=10;
                success_requests+=1;
            }
            else{
                cout<<"request deffered because of insufficient resources"<<endl;
                defered_requests+=1;
            }
        }
        
        
        if(total_score<25){
                cout<<"request deffered due to low score"<<endl;
                defered_requests+=1;
        }
        
        
        
        cout << endl;
        cout << "current resoures :" << endl;
        cout << "trucks: " << trucks << endl;
        cout << "supply packs: " << packs << endl;
        cout << endl;
    }


    //SUMMARY:
    cout<<"==============SUMMARY=================="<<endl;
    cout<<"total requests: "<<r<<endl;
    cout<<"successfull requests: "<<success_requests<<endl;
    cout<<"defered requests: "<<defered_requests<<endl;
    cout << "trucks left after "<<r<<" request/s : " << trucks << endl;
    cout << "supply packs left after "<<r<<" request/s : " << packs << endl;


    return 0;
}