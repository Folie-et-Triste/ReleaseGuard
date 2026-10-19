// Release Readiness demo / manual test (Issue #5: Readiness review)
// Build:  g++ releaseDemo.cpp -o release
// Run:    ./release

#include "release.h"

void report(release r){
    std::cout << "Release " << r.getVersion() << "  ->  " << r.getStatus() << "\n";
    std::vector<std::string> blockers = r.getBlockers();
    if(blockers.empty()){
        std::cout << "  All readiness rules passed. OK to approve.\n";
    } else {
        std::cout << "  Approval blocked:\n";
        for(size_t i = 0; i < blockers.size(); i++)
            std::cout << "   - " << blockers[i] << "\n";
    }
    std::cout << "\n";
}

int main(){
    
    std::cout << "=== ReleaseGuard: Readiness Review Demo ===\n\n";

    // Scenario 1: NOT ready - critical bug open, a test failing, checklist incomplete.
    release r1("1.2.0");
    r1.addBug({"Login crash", "Critical", false});
    r1.addTest({"smoke-test", true});
    r1.addTest({"auth-test", false});
    r1.addChecklistItem({"Release notes written", false});
    r1.updateStatus();
    report(r1);

    // Scenario 2: same release after everything is fixed - now Ready.
    release r2("1.2.1");
    r2.addBug({"Login crash", "Critical", true});
    r2.addTest({"smoke-test", true});
    r2.addTest({"auth-test", true});
    r2.addChecklistItem({"Release notes written", true});
    r2.updateStatus();
    report(r2);

    return 0;
}
