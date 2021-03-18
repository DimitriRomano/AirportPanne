<?php
include("dbconnect.php");
error_reporting(0);
// if(session_status()== PHP_SESSION_NONE){
//      session_start();
//  }
class Employee {
    protected $conn;
    protected $data = array();
    function __construct() {

                    $db = new dbObj();
                    $connString =  $db->getConnstring();
                    $this->conn = $connString;
    }
    // fonction getSelect permet de selectionner les vols
    // requete select pour la table d'affichage
    //jointure entre les deux tables vol et retard
    public function getSelect() {
        $sql = "SELECT DISTINCT  vol.depart ,vol.arrive , vol.horaire_depart,vol.horaire_arrive,retard.annulation FROM retard,vol
        WHERE vol.numero_vol = retard.numero_vol";
        // $sql="select distinct vol.depart ,vol.arrive , vol.horaire_depart,vol.horaire_arrive ,place_dispo,retard.annulation from vol natural join retard";
        //$sql4="select annulation from vol natural join retard";
        $queryRecords = pg_query($this->conn, $sql) or die("error to fetch flight data");
        $data = pg_fetch_all($queryRecords);
        return $data;
    }
//fonction getInsert permet d'inserer des reservation
//requete insert into
    public function getInsert(){
      if(isset($_POST['validate'])){

          $frome =$_POST['depart'];
          $too = $_POST['arrive'];
          $depart = $_POST['date_depart'];
          $class = $_POST['class_avion'];

      $sql1 ="INSERT INTO reservation( num_client , num_vol , depart , arrive , date_depart,classe_avion)
      VALUES('8','2','$frome' ,'$too' , '$depart' , '$class')";

       pg_query($this->conn,$sql1);

    }
  }
//fonction delete permet de supprimer des vols
//elle supprime que les vols qui sont annulées
  public function delete() {

      $sql2 = "DELETE FROM retard WHERE annulation=true";
      $rslt = pg_query($this->conn, $sql2);
  }


}
?>
