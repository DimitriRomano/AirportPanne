CREATE TABLE airport
(
    nom character varying(20)  NOT NULL,
    capacite_airport integer NOT NULL,
    type_avion_supporte character varying(20)  NOT NULL,
    CONSTRAINT airport_pkey PRIMARY KEY (nom)
)
CREATE TABLE avion
(
    numero_avion character varying(5)  NOT NULL,
    longitude character varying  NOT NULL,
    latitude character varying  NOT NULL,
    capacite integer NOT NULL,
    modele character varying  NOT NULL,
    capacite_bagage integer NOT NULL,
    CONSTRAINT avion_pkey PRIMARY KEY (numero_avion)
)
CREATE TABLE vol
(
    numero_vol character(5) NOT NULL,
    depart character varying(20) NOT NULL,
    arrive character varying(20) NOT NULL,
    horaire_depart time without time zone,
    horaire_arrive time without time zone,
    date_depart date,
    date_arrive date,
    trajet character varying[] ,
    numero_avion character varying(5) ,
    place_dispo integer,
    CONSTRAINT vol_pkey PRIMARY KEY (numero_vol),
    CONSTRAINT numero_avion FOREIGN KEY (numero_avion)
)
CREATE TABLE retard
(
    numero_retard character varying(8) NOT NULL,
    type_retard character varying(20)  NOT NULL,
    duree time without time zone,
    annulation boolean,
    numero_vol character varying(8),
    CONSTRAINT retard_pkey PRIMARY KEY (numero_retard),
    CONSTRAINT numero_vol FOREIGN KEY (numero_vol)
)

CREATE TABLE anomalies
(
    -- Inherited from table retard: numero_retard character varying(8)  NOT NULL,
    -- Inherited from table retard: type_retard character varying(20) NOT NULL,
    -- Inherited from table retard: duree time without time zone,
    -- Inherited from table retard: annulation boolean,
    numero_anomalies character varying(5),
    type_anomalies character varying 
    -- Inherited from table public.retard: numero_vol character varying(8) 
    CONSTRAINT anomalies_pkey PRIMARY KEY (numero_anomalies)
)
CREATE TABLE donnee_meteo
(
    -- Inherited from table retard: numero_retard character varying(8) NOT NULL,
    -- Inherited from table retard: type_retard character varying(20) NOT NULL,
    -- Inherited from table retard: duree time without time zone,
    -- Inherited from table retard: annulation boolean,
    zone character varying(20) NOT NULL,
    intemperies character varying ,
    vitesse_vent integer,
    -- Inherited from table retard: numero_vol character varying(8) ,
    CONSTRAINT donnee_meteo_pkey PRIMARY KEY (zone)
)
CREATE TABLE client
(
    num_client integer NOT NULL ,
    nom character varying(100) NOT NULL,
    prenom character varying(100) NOT NULL,
    email character varying(100) NOT NULL,
    tel character(100) NOT NULL,
    date_naissance date NOT NULL,
    username character varying(100) NOT NULL,
    password character varying(100) NOT NULL,
    CONSTRAINT client_pkey PRIMARY KEY (num_client)
)

CREATE TABLE reservation
(
    num_reservation integer NOT NULL ,
    num_client integer,
    num_vol character varying(8) ,
    depart character varying(30) ,
    destination character varying(30) ,
    date_depart date,
    classe_avion character varying(30) 
    CONSTRAINT reservation_pkey PRIMARY KEY (num_reservation)
)

