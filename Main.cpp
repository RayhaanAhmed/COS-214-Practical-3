#include <EventGroup.h>

#include <leaves/MarshalPost.h>
#include <leaves/MedicalStation.h>
#include <leaves/PitGarage.h>
#include <leaves/RunOffArea.h>
#include <leaves/TimingPoint.h>
#include <leaves/Grandstand.h>

int main() {

    // Root
    EventGroup root("Motorsport Event");

    // Circuit
    EventGroup* circuit = new EventGroup("Circuit");
    EventGroup* trackZone = new EventGroup("Track Zone");
    EventGroup* pitZone = new EventGroup("Pit Zone");

    // Circuit leaves
    trackZone->add(new MarshalPost("Marshal Post 1"));
    trackZone->add(new MarshalPost("Marshal Post 2"));
    trackZone->add(new TimingPoint("Timing Point 1"));
    trackZone->add(new TimingPoint("Timing Point 2"));

    pitZone->add(new PitGarage("Pit Garage 1"));
    pitZone->add(new PitGarage("Pit Garage 2"));

    circuit->add(trackZone);
    circuit->add(pitZone);
    circuit->add(new RunOffArea("Run-Off Area 1"));
    circuit->add(new RunOffArea("Run-Off Area 2"));

    // Spectator Area
    EventGroup* spectatorArea = new EventGroup("Spectator Area");

    spectatorArea->add(new Grandstand("Grandstand East"));
    spectatorArea->add(new Grandstand("Grandstand West"));

    // Race Administration
    EventGroup* raceAdministration =
        new EventGroup("Race Administration");

    raceAdministration->add(
        new MedicalStation("Medical Station 1")
    );
    raceAdministration->add(
        new MedicalStation("Medical Station 2")
    );

    // Build root
    root.add(circuit);
    root.add(spectatorArea);
    root.add(raceAdministration);

    // Test recursive operation
    root.reportStatus();

    return 0;
}

// Motorsport Event
// ├── Circuit
// │   ├── Track Zone
// │   │   ├── Marshal Post 1
// │   │   ├── Marshal Post 2
// │   │   ├── Timing Point 1
// │   │   └── Timing Point 2
// │   ├── Pit Zone
// │   │   ├── Pit Garage 1
// │   │   └── Pit Garage 2
// │   ├── Run-Off Area 1
// │   └── Run-Off Area 2
// ├── Spectator Area
// │   ├── Grandstand East
// │   └── Grandstand West
// └── Race Administration
//     ├── Medical Station 1
//     └── Medical Station 2