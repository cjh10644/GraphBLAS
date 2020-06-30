

    bool ok = true ;

    #pragma omp parallel for reduction(ok:&&) schedule (static)
    for (t =0 ; t < 1000000 ; t++)
    {
        p = malloc ( ) ;
        bool my_ok = (p != NULL) ;
        ok = ok && my_ok ;
        if (!my_ok) continue
        do stuff
    }


    if (!ok) { ... }



    bool all_ok [ntasks] ;
    #pragma omp parallel for
    for (int t = 0 ; t < ntasks ; t++)
    {
        p = malloc ( ) ;
        bool my_ok = (p != NULL) ;
        all_ok [t] = my_ok ;
        if (!my_ok) continue
        do stuff
    }


    bool ok = true ;
    for (int t = 0 ; t < ntasks ; t++)
    {
        ok = ok && all_ok [t] ;
    }


    bool all_ok [nthreads] ;
    for (int tid = 0 ; tid < nthreads ; tid++) all_ok [tid] = true ;
    #pragma omp parallel for num_threads(nthreads)
    for (int t = 0 ; t < ntasks ; t++)
    {
        tid = omp_get_thread_num ( ) ;
        p = malloc ( ) ;
        bool my_ok = (p != NULL) ;
        all_ok [tid] &&= my_ok ;
        if (!my_ok) continue
        do stuff
    }
    bool ok = true ;
    for (int tid = 0 ; tid < nthreads ; tid++)
    {
        ok = ok && all_ok [tid] ;
    }
