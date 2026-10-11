#include <iostream>
#include <iomanip>
using namespace std;


int main()
{
    char damage;
    int families;
    char route;
    char flood;
    char medneed;
    char prevaid;

    int damageScore = 0;
    int familyScore = 0;
    int routeScore = 0;
    int floodScore = 0;
    int medScore = 0;
    int aidPenalty = 0;
    int aidCut = 0;
    int medBonus = 0;
    int baseScore = 0;
    int needScore = 0;

    int trucks = 5;
    int packs = 120;

    int handled = 0;
    int deferredLow = 0;
    int deferredResource = 0;
    int requestNum = 1;

    char more = 'Y';

    while (more == 'Y' || more == 'y')
    {
        // Reset per-request scores so the next request starts clean.
        damageScore = 0;
        familyScore = 0;
        routeScore = 0;
        floodScore = 0;
        medScore = 0;
        aidPenalty = 0;
        aidCut = 0;
        medBonus = 0;
        baseScore = 0;
        needScore = 0;

        cout << "\nRequest R" << requestNum << endl;

        // Damage input with validation.
        cout << "Enter damage level (L/M/H): ";
        cin >> damage;
        while (damage != 'L' && damage != 'l' && damage != 'M' && damage != 'm' && damage != 'H' && damage != 'h')
        {
            cout << "Invalid damage level. Enter L, M or H: ";
            cin >> damage;
        }

        // Families input with range validation.
        cout << "Enter families affected (10-200): ";
        cin >> families;
        while (families < 10 || families > 200)
        {
            cout << "Families must be between 10 and 200. Re-enter: ";
            cin >> families;
        }

        // Route input with validation.
        cout << "Enter access route (O for Open / D for Damaged): ";
        cin >> route;
        while (route != 'O' && route != 'o' && route != 'D' && route != 'd')
        {
            cout << "Invalid route. Enter O or D: ";
            cin >> route;
        }

        // Flood warning input with validation.
        cout << "Enter flood warning (Y/N): ";
        cin >> flood;
        while (flood != 'Y' && flood != 'y' && flood != 'N' && flood != 'n')
        {
            cout << "Invalid entry. Enter Y or N: ";
            cin >> flood;
        }

        // Medical need input with validation.
        cout << "Enter medical need (Y/N): ";
        cin >> medneed;
        while (medneed != 'Y' && medneed != 'y' && medneed != 'N' && medneed != 'n')
        {
            cout << "Invalid entry. Enter Y or N: ";
            cin >> medneed;
        }

        // Previous aid input with validation.
        cout << "Enter previous aid received (Y/N): ";
        cin >> prevaid;
        while (prevaid != 'Y' && prevaid != 'y' && prevaid != 'N' && prevaid != 'n')
        {
            cout << "Invalid entry. Enter Y or N: ";
            cin >> prevaid;
        }

        // Damage is the primary driver of need, so it carries the highest weight.
        switch (damage)
        {
        case 'H':
        case 'h':
            damageScore = 30;
            break;
        case 'M':
        case 'm':
            damageScore = 15;
            break;
        case 'L':
        case 'l':
            damageScore = 5;
            break;
        }

        // Families are banded because displacement impact jumps at certain sizes.
        if (families >= 150)
        {
            familyScore = 25;
        }
        else if (families >= 100)
        {
            familyScore = 20;
        }
        else if (families >= 50)
        {
            familyScore = 10;
        }
        else
        {
            familyScore = 5;
        }

        // A damaged route means relief may not reach them later, so we act now.
        if (route == 'D' || route == 'd')
        {
            routeScore = 15;
        }
        else
        {
            routeScore = 0;
        }

        // A flood warning means the situation will get worse, not better.
        if (flood == 'Y' || flood == 'y')
        {
            floodScore = 10;
        }
        else
        {
            floodScore = 0;
        }

        // Medical need is time-critical: injured people cannot wait for supplies.
        if (medneed == 'Y' || medneed == 'y')
        {
            medScore = 15;
        }
        else
        {
            medScore = 0;
        }

        // Areas that already received aid are deprioritized so help rotates fairly.
        if (prevaid == 'Y' || prevaid == 'y')
        {
            aidPenalty = 10;
        }

        // If they already got aid and damage is low, they are likely stabilized,
        // so we free up resources for worse-hit areas.
        if ((prevaid == 'Y' || prevaid == 'y') && (damage == 'L' || damage == 'l'))
        {
            aidCut = 5;
        }

        // Medical need combined with a damaged route is life-threatening,
        // because help physically cannot reach them in time.
        if ((medneed == 'Y' || medneed == 'y') && (route == 'D' || route == 'd'))
        {
            medBonus = 10;
        }

        baseScore = damageScore + familyScore + routeScore + floodScore + medScore;

        needScore = baseScore - aidPenalty - aidCut + medBonus;

        // Cap the score at 100 so decision thresholds stay predictable.
        if (needScore > 100)
        {
            needScore = 100;
        }

        // Floor the score at 0, since a "negative urgency" makes no sense.
        if (needScore < 0)
        {
            needScore = 0;
        }



        // Print the request info in readable form.
        cout << "\n===================Request Info=================" << endl;
        cout <<left<<setw(22)<< "Damage: ";
        if (damage == 'H' || damage == 'h')
        {
            cout <<left<<setw(16)<< "High" << endl;
        }
        else if (damage == 'M' || damage == 'm')
        {
            cout <<left<<setw(16)<< "Medium" << endl;
        }
        else
        {
            cout <<left<<setw(16)<< "Low" << endl;
        }

        cout << left<<setw(22)<<"Families: " <<left<<setw(10)<< families << endl;

        cout << left<<setw(22)<<"Route: ";
        if (route == 'D' || route == 'd')
        {
            cout<<left<<setw(16) << "Damaged" << endl;
        }
        else
        {
            cout<<left<<setw(16) << "Open" << endl;
        }

        cout <<left<<setw(22)<< "Flood Warning: ";
        if (flood == 'Y' || flood == 'y')
        {
            cout <<left<<setw(16)<< "Yes" << endl;
        }
        else
        {
            cout <<left<<setw(16)<< "No" << endl;
        }

        cout << left<<setw(22)<<"Medical Need: ";
        if (medneed == 'Y' || medneed == 'y')
        {
            cout <<left<<setw(10)<< "Yes" << endl;
        }
        else
        {
            cout <<left<<setw(10)<< "No" << endl;
        }

        cout <<left<<setw(22)<< "Previous Aid: ";
        if (prevaid == 'Y' || prevaid == 'y')
        {
            cout<<left<<setw(10) << "Yes" << endl;
        }
        else
        {
            cout<<left<<setw(10) << "No" << endl;
        }

        cout <<left<<setw(22)<< "Need Score: "<<left<<setw(10) << needScore << endl;

        // Choose the intended action from the score thresholds.
        char intendedAction = 'D';
        if (needScore >= 80)
        {
            intendedAction = 'A';
        }
        else if (needScore >= 60)
        {
            intendedAction = 'B';
        }
        else if (needScore >= 40)
        {
            intendedAction = 'C';
        }
        else
        {
            intendedAction = 'D';
        }

        // Fall back one level at a time until the action fits or we reach D.
        // D costs nothing, so the loop always resolves.
        char action = intendedAction;
        int trucksNeeded = 0;
        int packsNeeded = 0;

        while (true)
        {
            // Look up the cost of the current action.
            switch (action)
            {
            case 'A':
                trucksNeeded = 2;
                packsNeeded = 50;
                break;
            case 'B':
                trucksNeeded = 1;
                packsNeeded = 30;
                break;
            case 'C':
                trucksNeeded = 1;
                packsNeeded = 10;
                break;
            default:
                trucksNeeded = 0;
                packsNeeded = 0;
                break;
            }

            // If the action fits or we've reached D, stop.
            if ((trucks >= trucksNeeded && packs >= packsNeeded) || action == 'D')
            {
                break;
            }

            // Otherwise drop one level and try again.
            action++;
        }

        // If the action changed, tell the user why and which resource was short.
        if (action != intendedAction)
        {
            cout << "\nDue to unavailability of resources, action " << intendedAction << " could not be processed, so action " << action << " was processed instead." << endl;

            // Report which specific resource was short.
            int originalTrucks = 0;
            int originalPacks = 0;

            switch (intendedAction)
            {
            case 'A':
                originalTrucks = 2;
                originalPacks = 50;
                break;
            case 'B':
                originalTrucks = 1;
                originalPacks = 30;
                break;
            case 'C':
                originalTrucks = 1;
                originalPacks = 10;
                break;
            }

            if (trucks < originalTrucks)
            {
                cout << "Reason: only " << trucks << " truck(s) available, " << originalTrucks << " needed." << endl;
            }

            if (packs < originalPacks)
            {
                cout << "Reason: only " << packs << " pack(s) available, " << originalPacks << " needed." << endl;
            }
        }

        // Deduct resources and report the outcome.
        trucks = trucks - trucksNeeded;
        packs = packs - packsNeeded;

        cout << "\n"<<left<<setw(22)<<"Action Processed: ";

        if (action == 'A')
        {
            cout << "A - Full Relief" << endl;
        }
        else if (action == 'B')
        {
            cout << "B - Standard Relief" << endl;
        }
        else if (action == 'C')
        {
            cout << "C - Emergency Kit Only" << endl;
        }
        else
        {
            cout << "D - Defer / Monitor" << endl;
        }

        cout << left<<setw(22)<<"Trucks Used: " << trucksNeeded << endl;
        cout << left<<setw(22)<<"Packs Used: " << packsNeeded << endl;
        cout << left<<setw(22)<<"Trucks Remaining: " << trucks << endl;
        cout << left<<setw(22)<<"Packs Remaining: " << packs << endl;

        // Deferral is decided purely by whether the final action is D.
        if (action == 'D')
        {
            if (intendedAction == 'D')
            {
                deferredLow++;
                cout << "Reason: need score was too low for any relief." << endl;
            }
            else
            {
                deferredResource++;
                cout << "Reason: not enough resources for any relief action." << endl;
            }
        }
        else
        {
            handled++;
        }

        requestNum++;

        cout << "\nProcess another request? (Y/N): ";
        cin >> more;
    }

    cout << "\n====================Summary=======================" << endl;
    cout << left<<setw(20)<<"Requests Handled: " <<right<<setw(15)<< handled << endl;
    cout <<left<<setw(20)<< "Deferred (low need): "<<right <<setw(14)<< deferredLow << endl;
    cout << left<<setw(20)<<"Deferred (no resources): " <<right<<setw(10)<< deferredResource << endl;
    cout <<left<<setw(20)<< "Total Deferred: " <<right<<setw(15)<< deferredLow + deferredResource << endl;
    cout <<left<<setw(20)<< "Trucks Left: " <<right<<setw(15)<< trucks << endl;
    cout <<left<<setw(20)<< "Packs Left: " <<right<<setw(15)<< packs << endl;

    return 0;
}