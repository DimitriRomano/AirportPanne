<?php
$dbhost = 'localhost';
$dbname = 'db2019l3i_dromano';
$dbuser = 'postgres';
$dbpass = 'dim';
// $dbhost = '10.40.128.23';
// $dbname = 'db2019l3i_dromano';
// $dbuser = 'y2019l3i_dromano';
// $dbpass = 'A123456*';

$q      = $_POST['query'];
$action = $_POST['action'];

//on etablie la connexion avec la base de donnees
$dbconn = pg_connect("host=$dbhost dbname=$dbname user=$dbuser password=$dbpass")
 or die('Could not connect: ' . pg_last_error());
// on recupere les donnees inserer dans le premier select
//avec la requete select on selectionne les villes de destination qui ont la ville de depart selectionner precedemment
//on change le nombre de place dispo on fonction des reservations.
$output = '';
if ($action === 'depart') {
    $query = "SELECT arrive FROM vol where depart = '" . $q . "'";
    $result = pg_query($query) or die('Error message: ' . pg_last_error());
    $sql = "UPDATE vol SET place_dispo=place_dispo-1 where depart = '" . $q . "'";
    $rest = pg_query($sql);
    while ($row = pg_fetch_row($result)) {
        foreach ($row as $value) {
            $output .= '<option value="' . $value . '">' . $value . '</option>';
        }
    }


    echo $output;
}
?>
