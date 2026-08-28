# Job Data
set Jobs := { read "jobs.txt" as "<1s>" comment "#"
};

# earliest beginning of job
param release [Jobs] := read "jobs.txt" as "<1s> 2n" comment "#";

# latest end of job
param due     [Jobs] := read "jobs.txt" as "<1s> 3n" comment "#";

param duration[Jobs] := read "jobs.txt" as "<1s> 4n" comment "#";

set Drivers := { 1 to 7 };
param Shifts := 2;

# constants
param sum_dur := sum<j> in Jobs : duration[j];
param min_dur := min<j> in Jobs : duration[j];
param min_rel := min<j> in Jobs : release[j];
param max_due := max<j> in Jobs : due[j];

#########################
# Variable declaration
var job_beg [<j> in Jobs] >= release[j] <= due[j]-duration[j];
var assign[Jobs * Drivers * { 1 to Shifts }] binary;
var sequ[Jobs * Jobs] binary;
var wrk_beg [Drivers * { 1 to Shifts }] >= min_rel <= max_due - min_dur;
var wrk_end [Drivers * { 1 to Shifts }] >= min_rel <= max_due;

#########################
# Objective: minimize the time a worker is not assigned a job
minimize wrk_wait:
   sum<d,s> in Drivers * { 1 to Shifts } :
	  (wrk_end[d,s] - wrk_beg[d,s]) - sum_dur;


# Ensure that processing of an job_begs after the release date
# and is completed before the due date
#subto job_beg_range:
#forall <j> in Jobs :
#   job_beg[j] <= due[j] - 
#         sum<d,s> in Drivers * { 1 to Shifts } : assign[j,d,s] * 
#         duration[j];

# Assigment constraints, one machine per job
subto job_assignment:
forall <j> in Jobs :
   sum<d,s> in Drivers * { 1 to Shifts } : 
      assign[j,d,s] == 1;

# Jobs assigned to driver should be less than his work_time
subto cut1:
forall<d,s> in Drivers * { 1 to Shifts } :
   sum<j> in Jobs : assign[j,d,s] * duration[j] <= wrk_end[d,s] - wrk_beg[d,s];

# order does not matter (sequ[i,j] = 0), if jobs i and j are on different machines
#subto job_order_between:
#forall<d,s> in Drivers * { 1 to Shifts } :
#   forall<e,t> in Drivers * { 1 to Shifts } with d != e and s != t:
#      forall<i> in Jobs :
#         forall<j> in Jobs with j > i :
#            sequ[i,j] + sequ[j,i] <= 2 - assign[i,d,s] - assign[j,e,t];

# Jobs must be processed one after the other, if processed on same machine
subto job_order_same:
forall<d,s> in Drivers * { 1 to Shifts } :
   forall<i> in Jobs :
      forall<j> in Jobs with j > i :
         sequ[i,j] + sequ[j,i] >= assign[i,d,s] + assign[j,d,s] - 1;

# Only one job is before the other
subto job_order_distinct:
forall<i> in Jobs :
   forall<j> in Jobs with j > i :
      sequ[i,j] + sequ[j,i] <= 1;

# All jobs j following job i on the same machine (have sequ[i,j]=1) must start after i is finished
subto sequencing:
forall<i> in Jobs :
   forall<j> in Jobs with i != j :
      job_beg[i] +
#            sum<d,s> in Drivers * { 1 to Shifts } : assign[i,d,s] * 
            duration[i] - job_beg[j]
            <= (max_due - min_rel) * (1 - sequ[i,j]);

#########################
# Cuts
subto cut:
forall<d,s> in Drivers * { 1 to Shifts } :
   forall<i> in Jobs :
      forall<j> in Jobs with release[i] < due[j] :
#         sum<k> in Jobs with release[k] >= release[i] and due[k] <= due[j] :
#            duration[k] * assign[k,d,s]
         sum<k> in Jobs :
            min(due[j] - release[i], max(duration[k] - max(max(release[i]-release[k],0), max(due[k]-due[j],0)), 0)) * assign[k,d,s]
         <= due[j] - release [i];


#####################
# jobs must be done inside working times
subto work_begin:
forall<d,s> in Drivers * { 1 to Shifts } :
   forall<j> in Jobs :
      wrk_beg [d,s] - job_beg [j] <= (1 - assign[j,d,s]) * max_due;

subto work_end:
forall<d,s> in Drivers * { 1 to Shifts } :
   forall<j> in Jobs :
      job_beg [j] + duration[j] - wrk_end [d,s] <= (1 - assign[j,d,s]) * max_due;


#########################
# working time constraints
subto daywork:
forall<d,s> in Drivers * { 1 to Shifts } :
   0 <= wrk_end[d,s] - wrk_beg[d,s] <= 10;

subto pausetime:
forall<d,s> in Drivers * { 1 to Shifts-1 } :
   wrk_beg[d,s+1] - wrk_end[d,s] >= 9;

subto weekwork:
forall<d> in Drivers:
   sum<s> in { 1 to Shifts } : (wrk_end[d,s] - wrk_beg[d,s]) <= 56;
