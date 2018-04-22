mat getadamdelta_bo(const vec &delta_bo){

        bomt = BETA_1*bomt+(1-BETA_1)*delta_bo;
        bovt = BETA_2*bovt+(1-BETA_2)*square(delta_bo);

        vec bomt_ = (1.0/(1-BETA_1))*bomt;
        vec bovt_ = (1.0/(1-BETA_2))*bovt;

        return kroncker(bomt_,(reciprocal(evolution(bovt_)+ESPSILON)));

    }