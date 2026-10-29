#include <iostream>
#include <cassert>
#include "release.h"

void runTests() {

    // -------------------------------------------------------------
    // TEST 1: Reject
    // -------------------------------------------------------------
    std::cout << "[Test 1] Rejecting a release with a reason...\n";
    release rel1("v1.0.0");
    rel1.submitReleaseRequest("DevUser1", "Feature release v1.0.0");

    rel1.rejectRelease("QA_Lead", "Critical security flaw detected.");
    
    assert(rel1.getStatus() == "Rejected");
    assert(rel1.getReviewedBy() == "QA_Lead");
    assert(rel1.getRejectionReason() == "Critical security flaw detected.");
    std::cout << " -> PASSED!\n\n";

    // -------------------------------------------------------------
    // TEST 2: Reject 
    // -------------------------------------------------------------
    std::cout << "[Test 2] Rejecting without a reason (should fail)...\n";
    release rel2("v1.1.0");
    rel2.submitReleaseRequest("DevUser2", "Minor update");

    rel2.rejectRelease("QA_Lead", ""); 
    
    assert(rel2.getStatus() != "Rejected");
    std::cout << " -> PASSED!\n\n";

    // -------------------------------------------------------------
    // TEST 3: Approval failed
    // -------------------------------------------------------------
    std::cout << "[Test 3] Approving a release with active blockers (should fail)...\n";
    release rel3("v2.0.0");
    rel3.submitReleaseRequest("DevUser3", "Major release with bug");

    
    bug b1{"Memory Leak", "Critical", false};
    rel3.addBug(b1);

    rel3.approveRelease("ReleaseManager");

    assert(rel3.getStatus() != "Approved"); // Debe fallar la aprobación
    std::cout << " -> PASSED!\n\n";


    std::cout << "[Test 4] Approving a clean release...\n";
    release rel4("v2.1.0");
    rel4.submitReleaseRequest("DevUser4", "Stable patch");

    
    testResult t1{"Unit Tests", true};
    checklistItem c1{"Documentation updated", true};
    rel4.addTest(t1);
    rel4.addChecklistItem(c1);

    rel4.approveRelease("ReleaseManager");

    assert(rel4.getStatus() == "Approved");
    assert(rel4.getReviewedBy() == "ReleaseManager");
    std::cout << " -> PASSED!\n\n";

}

int main() {
    runTests();
    return 0;
}