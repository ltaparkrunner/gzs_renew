#ifndef TRACKBAR_H
#define TRACKBAR_H

#include <QTime>
#include "simpletable.h"

struct trackBar{
    int pos;
//    int
    int posChanged(simpleTable stbl){
        try{
            QTime RegimeTime = stbl.dt[pos].duration;
            // RegimeTime output to current time

            QTime TotalTime =QTime::fromString("00:00:00", "hh:mm:ss");
            int ln = stbl.dt.length();
            for(int row = pos; row<stbl.dt.length(); row++)
                TotalTime = TotalTime + stbl.dt[row].duration;
            // TotalTime output to TotalTime
        }
        catch(...){
            //  output ???
            //  output ???
        }
        stbl.checkTable();
        // output Flow_gas, Flow_air, Flow_vlag_gas, C_mix
        return 0;
    }
};

#endif // TRACKBAR_H
