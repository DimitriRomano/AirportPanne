<?php
// $dbhost = '10.40.128.23';
// $dbname = 'db2019l3i_dromano';
// $dbuser = 'y2019l3i_dromano';
// $dbpass = 'A123456*';

$dbhost = 'localhost';
$dbname = 'db2019l3i_dromano';
$dbuser = 'postgres';
$dbpass = 'dim';

//on etablie la connexion avec la base de donnees
$dbconn = pg_connect("host=$dbhost dbname=$dbname user=$dbuser password=$dbpass")
 or die('Could not connect: ' . pg_last_error());
//on recupere les donnees inserer dans les champs
//on verifie d'abord si l'utilisateur existe dans la base de donnees
//on verifie si le mot de passe saisi est bien crypté avec la fonction password_verify
//si c le cas on ouvre une session

if (isset($_POST['signin'])) {

    $username = $_POST['username'];
    $password = $_POST['password'];
    if (empty($username) || empty($password)) {
      header("Location: ../index.php?error=emptyfields");
      exit();
    }else {
      $sql = "SELECT * FROM client WHERE username ='$username'";
      $result = pg_query($sql) or die('Error message: ' . pg_last_error());
      if ($result==false) {
        header("Location: ../index.php?error=sqlerror");
        exit();
      }else {

        if ($row = pg_fetch_assoc($result)) {
          $pass = $row['password'];
          $pwdCheck = password_verify($password,$pass);

          if ($pwdCheck == false) {
            header("Location: ../index.php?error=wrongpassword");
            exit();
          }
          elseif ($pwdCheck == true) {
            session_start();
            $_SESSION['username'] =$row['username'];
            header("Location:account.php?login=success");
            exit();
          }
        }else {
          header("Location: ../index.php?error=nouser");
          exit();
        }
      }
    }
}else {
  header("Location: ../index.php");
  exit();
} ?>
