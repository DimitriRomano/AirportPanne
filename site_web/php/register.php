<!DOCTYPE html>
<html lang="fr" dir="ltr">
  <head>
    <meta charset="utf-8">
    <title>SIGN IN</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" type="text/css" href="../css/Bootstrap.min.css">
    <link rel="shortcut icon" href="images/logo.JPG" type="image/x-icon">
    <link href="//maxcdn.bootstrapcdn.com/font-awesome/4.2.0/css/font-awesome.min.css" rel="stylesheet">
    <link href="https://fonts.googleapis.com/css?family=Big+Shoulders+Text&display=swap" rel="stylesheet">
    <script src="https://code.jquery.com/jquery-3.4.1.js"></script>
    <script src="../js/bootstrap.min.js"></script>
    <link rel="stylesheet" href="../css/fixed.css">

  </head>
  <body>
    <div class="container">
      <div class="row">
        <div class="col-md-7">
          <div class="row">
            <div class="col-md-5">
              <h3 class="text-center">Registration Form</h3>
            </div>
            <div class="col-md-6">
              <span class="glyphicon glyphicon-pencil"></span>
            </div>
          </div>
          <hr>
          <form action="#" method="post">
          <div class="row">
            <label class="label col-md-2 control-label">Nom</label>
            <div class="col-md-8">
              <input type="text" class="form-control" name="nom" id="nom"  placeholder="Nom" required>
            </div>
          </div>

          <div class="row">
            <label class="label col-md-2 control-label">Prenom</label>
            <div class="col-md-8">
              <input type="text" class="form-control" name="prenom" id="prenom"  placeholder="Prenom" required>
            </div>
          </div>
          <div class="row">
            <label class="label col-md-2 control-label">Email</label>
            <div class="col-md-8">
              <input type="text" class="form-control" name="email" id="email"  placeholder="E-mail" required>
            </div>
          </div>
          <div class="row">
            <label class="label col-md-2 control-label">Password</label>
            <div class="col-md-8">
              <input type="password" class="form-control" name="password" id="password"  placeholder="Password" required>
            </div>
          </div>

          <div class="row">
            <label class="label col-md-2 control-label">Username</label>
            <div class="col-md-8">
              <input type="text" class="form-control" name="username" id="username"  placeholder="CHOOSE YOUR USERNAME" required>
            </div>
          </div>
          <div class="row">
            <label class="label col-md-2 control-label">Telephone</label>
            <div class="col-md-8">
              <input type="text" class="form-control" name="telephone" id="telephone"  placeholder="Telephone" required>
            </div>
          </div>
          <div class="row">
            <label class="label col-md-2 control-label">Date De Naissance</label>
            <div class="col-md-8">
              <input type="date" class="form-control" name="naissance" id="naissance"  placeholder="Date De Naissance" required>
            </div>
          </div>

            </div>
          </div>
          <div class="text-left">
            <button type="submit" name="submit_signup" class="btn btn-dark">SIGN UP</button>
          </div>
        </div>
      </form>
      </div>
    </div>
  </body>
</html>


<?php

$dbhost = '10.40.128.23';
$dbname = 'db2019l3i_dromano';
$dbuser = 'postgres';
$dbpass = 'dim';
//on etablie la connexion avec la base de donnees
$dbconn = pg_connect("host=$dbhost dbname=$dbname user=$dbuser password=$dbpass")
 or die('Could not connect: ' . pg_last_error());
//on recupere les donnees inserer dans les champs
//on crypte le mot de passe avec la fonction password_hash
//on insert les donnees dans la base grace a la requete insert into
if(isset($_POST['submit_signup'])){

    $nom =$_POST['nom'];
    $prenom = $_POST['prenom'];
    $email = $_POST['email'];
    $password = $_POST['password'];
    $username = $_POST['username'];
    $telephone = $_POST['telephone'];
    $naissance = $_POST['naissance'];

$hash = password_hash($password , PASSWORD_BCRYPT);
$sql1 ="INSERT INTO client (nom , prenom , email , tel , date_naissance , username , password)
VALUES('$nom','$prenom','$email','$telephone','$naissance','$username','$hash')";
pg_query($sql1);
}

 ?>
