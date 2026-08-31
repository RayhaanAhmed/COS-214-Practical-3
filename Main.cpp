#include "EventGroup.h"
#include "EventControl.h"
#include "EventNotice.h"

#include "MarshalPost.h"
#include "MedicalStation.h"
#include "PitGarage.h"
#include "RunOffArea.h"
#include "TimingPoint.h"
#include "Grandstand.h" 
#include "SafetyCar.h" // spec 4.4 original feature (7th leaf type)

int main() {
    //Composite construction
    EventGroup* root = new EventGroup("Motorsport Event");

    EventGroup* circuit = new EventGroup("Circuit");
    EventGroup* trackZone = new EventGroup("Track Zone");
    EventGroup* pitZone = new EventGroup("Pit Zone");

    trackZone->add(new MarshalPost("Marshal Post 1"));
    trackZone->add(new MarshalPost("Marshal Post 2"));
    trackZone->add(new TimingPoint("Timing Point 1")); 
    trackZone->add(new TimingPoint("Timing Point 2"));

    PitGarage* garage1 = new PitGarage("Pit Garage 1"); //default capacity 4
    pitZone->add(garage1);
    pitZone->add(new PitGarage("Pit Garage 2"));

    circuit->add(trackZone);
    circuit->add(pitZone);
    circuit->add(new RunOffArea("Run-Off Area 1"));
    circuit->add(new RunOffArea("Run-Off Area 2"));
    circuit->add(new SafetyCar("Safety Car 1")); //extra feature 1

    EventGroup* spectatorArea = new EventGroup("Spectator Area");
    Grandstand* east = new Grandstand("Grandstand East", 300);
    east->setOccupancy(280);
    spectatorArea->add(east);
    spectatorArea->add(new Grandstand("Grandstand West", 300));

    EventGroup* raceAdministration = new EventGroup("Race Administration");
    raceAdministration->add(new MedicalStation("Medical Station 1"));
    raceAdministration->add(new MedicalStation("Medical Station 2"));

    root->add(circuit);
    root->add(spectatorArea);
    root->add(raceAdministration);

    //Observer registration
    //EventControl as root Subject, top-level groups observe it.
    EventControl control(root);
    control.attach(circuit);
    control.attach(spectatorArea);
    control.attach(raceAdministration);

    //Composite traversal/query
    std::cout << "Initial status (recursive traversal)\n";
    root->reportStatus();
    std::cout << "Total capacity (recursive query): " << root->getCapacity() << "\n";

    //8.1: notice type 1/3 + 8.1: cascading notification
    //3+ runtime levels: EventControl -> Circuit -> Track/Pit Zone -> leaves
    EventNotice redFlag("RED_FLAG", "", "session stopped", 5);
    control.issueNotice(redFlag);

    //8.1: notice type 2/3
    //[SPEC 4.3] Grandstand::update() branches on occupancy vs capacity
    //for CAPACITY_ALERT= a real alt-style [severity/threshold] guard.
    EventNotice capacityAlert("CAPACITY_ALERT", "Spectator Area", "grandstand approaching capacity", 3);
    control.issueNotice(capacityAlert);

    EventNotice resume("RESUME", "", "session resumes", 1);
    control.issueNotice(resume);

    //weather-severity auto-escalation (extra feature 2)
    std::cout << "\nDemonstrating original feature 2: weather-severity escalation\n";
    EventNotice severeWeather("WEATHER_ALERT", "", "storm cell over Sector 1", 5);
    control.issueNotice(severeWeather); // severity 5 >= 4 -> marshal posts auto-escalate to RED
    control.issueNotice(resume); // clear back to green

    //Original feature 3 : PitGarage bounded queue
    std::cout << "\nDemonstrating original feature 3: PitGarage bounded queue\n";
    garage1->enqueueCar("Car #1");
    garage1->enqueueCar("Car #2");
    garage1->enqueueCar("Car #3");
    garage1->enqueueCar("Car #4");
    garage1->enqueueCar("Car #5"); //capacity is 4 so this one is rejected

    // SPEC 4.3 = explicit condition-based decision, standalone demo
    // Two-branch alt: [occupancy >= capacity] self-issues CAPACITY_ALERT,
    // [else] does nothing.( See EventGroup::checkCapacityThreshold() )
    std::cout << "\nDemonstrating 4.3 condition-based decision (alt guard)\n";
    spectatorArea->checkCapacityThreshold(250); //branch: below capacity
    spectatorArea->checkCapacityThreshold(650); //branch: at/above capacity = alert

    //registration change
    std::cout << "\nDetaching Race Administration from EventControl\n";
    control.detach(raceAdministration);

    //8.1: notice type 3/3
    EventNotice weather("WEATHER_ALERT", "", "rain incoming", 2);
    control.issueNotice(weather); // raceAdministration will NOT react (detached) but others will

    //8.1: runtime reorganisation
    // Move Pit Garage 1 from Pit Zone to Race Administration. Composite
    // ownership AND Observer registration are both updated
    // EventGroup::add()/remove(). shows it 
    std::cout << "\nRuntime reorganisation: moving Pit Garage 1 to Race Administration from Pit Zone\n";
    pitZone->remove(garage1);// ownership released, not deleted
    raceAdministration->add(garage1); // new parent owns it + re-attaches as observer
    control.attach(raceAdministration); // re-attach since it was detached above
    EventNotice pitClosed("PIT_LANE_CLOSED", "", "lane closed for recovery vehicle", 2);
    control.issueNotice(pitClosed);// garage1 now reachable via Race Administration's cascade

    std::cout << "\n--- Final status before shutdown ---\n";
    root->reportStatus();

    // 8.1: clean shutdown
    // Deleting root deletes the entire owned subtree exactly once
    // (verified leak- and double-free-free under AddressSanitizer).
    std::cout << "\n--- Deleting root (cascading destruction) ---\n";
    delete root;
    return 0;
}


