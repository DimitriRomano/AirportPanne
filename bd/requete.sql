--1
SELECT COUNT(depart)  FROM vol
WHERE depart='PARIS';
--2

INSERT INTO reservation(depart , destination , date_depart,classe_avion) VALUES('PARIS','AMSTERDAM','01/01/2020','Business');

--3
DELETE FROM retard WHERE annulation=true;

--4
select distinct vol.depart ,vol.arrive , vol.horaire_depart,vol.horaire_arrive ,place_dispo,retard.annulation from vol natural join retard;

--5
SELECT * FROM client WHERE username ='Adam';

--6
UPDATE vol SET place_dispo=place_dispo-1 where depart ='PARIS';

--7
SELECT depart FROM vol GROUP BY depart ORDER BY depart ASC;
 
--8
SELECT *
FROM retard,vol
WHERE vol.numero_vol=retard.numero_retard
AND annulation=false;
--9
SELECT *FROM vol WHERE place_dispo >'2';
--10
INSERT INTO client (nom , prenom , email , tel , date_naissance , username , password)
values ('Marc' ,'BAH' , 'marc@live.fr' , '09345454' , '02/12/1999','marc' ,'$2y$10$giBpT0XWiBWbQ9EV6vAkx.gPIM.H5ey1gn5dPTFRmCeupCrZoayQS' );