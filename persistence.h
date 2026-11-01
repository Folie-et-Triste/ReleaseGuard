#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include "release.h"
#include <fstream>
#include <sstream>

// Simple line-based persistence (no external dependency).
//   RELEASE|version|status|requestedBy|description
//   BUG|title|severity|assignee|resolved(0/1)
//   TEST|name|passed(0/1)
//   CHECK|description|complete(0/1)
//   ===

inline std::vector<std::string> splitFields(const std::string &line, char d){
    std::vector<std::string> parts; std::string cur; std::istringstream iss(line);
    while(std::getline(iss, cur, d)) parts.push_back(cur);
    return parts;
}

inline void saveReleases(std::vector<release> &releases, const std::string &path = "releases.txt"){
    std::ofstream out(path);
    for(size_t i=0;i<releases.size();i++){
        release &r = releases[i];
        out << "RELEASE|" << r.getVersion() << "|" << r.getStatus() << "|"
            << r.getRequestedBy() << "|" << r.getDescription() << "\n";
        std::vector<bug> bs = r.getBugs();
        for(size_t j=0;j<bs.size();j++)
            out << "BUG|" << bs[j].title << "|" << bs[j].severity << "|"
                << bs[j].assignee << "|" << (bs[j].resolved?1:0) << "\n";
        std::vector<testResult> ts = r.getTests();
        for(size_t j=0;j<ts.size();j++)
            out << "TEST|" << ts[j].name << "|" << (ts[j].passed?1:0) << "\n";
        std::vector<checklistItem> cs = r.getChecklist();
        for(size_t j=0;j<cs.size();j++)
            out << "CHECK|" << cs[j].description << "|" << (cs[j].complete?1:0) << "\n";
        out << "===\n";
    }
}

inline std::vector<release> loadReleases(const std::string &path = "releases.txt"){
    std::vector<release> releases;
    std::ifstream in(path);
    if(!in) return releases;
    std::string line; bool have=false; release temp("");
    while(std::getline(in, line)){
        if(line == "==="){ if(have){ releases.push_back(temp); have=false; } continue; }
        std::vector<std::string> p = splitFields(line, '|');
        if(p.empty()) continue;
        if(p[0]=="RELEASE"){
            if(have) releases.push_back(temp);
            temp = release(p.size()>1?p[1]:"");
            if(p.size()>3) temp.setRequestedBy(p[3]);
            if(p.size()>4) temp.setDescription(p[4]);
            if(p.size()>2) temp.setStatus(p[2]);
            have=true;
        } else if(p[0]=="BUG" && have){
            bug b; b.title=p.size()>1?p[1]:""; b.severity=p.size()>2?p[2]:"";
            b.assignee=p.size()>3?p[3]:""; b.resolved=(p.size()>4 && p[4]=="1");
            temp.addBug(b);
        } else if(p[0]=="TEST" && have){
            testResult t; t.name=p.size()>1?p[1]:""; t.passed=(p.size()>2 && p[2]=="1");
            temp.addTest(t);
        } else if(p[0]=="CHECK" && have){
            checklistItem c; c.description=p.size()>1?p[1]:""; c.complete=(p.size()>2 && p[2]=="1");
            temp.addChecklistItem(c);
        }
    }
    if(have) releases.push_back(temp);
    return releases;
}

#endif // PERSISTENCE_H
