<?php
include("select.php");
if(session_status()== PHP_SESSION_NONE){
  session_start();
// Store Session Data
}
$newObj = new Employee();
$emps = $newObj->getSelect();
$ins = $newObj->getInsert();
$del = $newObj->delete();

?>
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Our-Airport||Officiel WebSite</title>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.0/jquery.min.js"></script>
    <link rel="stylesheet" type="text/css" href="../css/bootstrap.min.css">
    <link rel="stylesheet" href="../css/bootstrap-4.1.3-dist/css/bootstrap.min.css">
    <link rel="stylesheet" type="text/css" href="../style.css">
    <link href="//maxcdn.bootstrapcdn.com/font-awesome/4.2.0/css/font-awesome.min.css" rel="stylesheet">
    <script src="https://code.jquery.com/jquery-3.4.1.js"></script>
    <script src="../js/bootstrap.min.js"></script>
    <script src="../js/permutation.js"></script>

    <link rel="stylesheet" href="../css/fixed.css">
<style type="text/css">
.home-inner{
  background-image: url(../img/blog_11.jpg);
}
.caption {
  width: 100%;
  max-width: 100%;
  position: absolute;
  top: 38%;
  z-index: 1;
  color: white;
  text-transform: uppercase;
}

.caption h1{
  font-size: 3.8rem;
  font-weight: 700;
  letter-spacing: .3rem;
  text-shadow: .1rem .1rem .8rem black;
}

caption h3{
  font-size: 2rem;
  text-shadow: .1rem .1rem .5rem black ;
  padding-bottom: 1.6rem;
}


</style>
</head>

<body data-spy="scroll" data-target="#navbarResponsive">
    <!-- Start Home Section  -->
    <div id="home">

    </div>
    <!-- END Home Section  -->

    <!--Start Navigation Section -->
    <nav class="navbar navbar-expand-md navbar-dark bg-dark fixed-top">
        <a class="navbar-brand" href="#">
            <img src="../img/logo_aeroport.JPG" alt="logo imag"> Our-Airport</a>
        <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarResponsive">
            <span class="navbar-toggler-icon"></span>
        </button>
        <h4 style="color:white; text-align:center;"><?php echo"Hi ".$_SESSION['username'];?></h4>

        <div class="collapse navbar-collapse" id="navbarResponsive">
            <ul class="navbar-nav ml-auto">
                <li class="nav-item">
                    <a class="nav-link" href="#home">Home</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="#reservation">Reservation</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="#about">About</a>
                </li>
            </ul>
        </div>

    </nav>
    <!-- Navigation Section  -->

    <!-- Start Landing Page Section  -->
    <div class="landing">
        <div class="home-wrap">
            <div class="home-inner">

            </div>
        </div>
    </div>

    <div class="caption text-center">
        <h1>Welcome to Cergy-Airport</h1>
        <h3>The Best Airport Ever</h3>
    </div>
    <!-- END Landing Page Section  -->
<?php

 ?>

    <!-- Start Reserve Section  -->
    <!-- On selectionne les villes de depart  -->
    <!-- On selectionne les villes d'arrivee en fontion de ce qu'on a choisit on ville de depart  -->
    <div class="jumbotron" style="background-color: rgb(115, 117, 129);">
        <div class="narrow text-center">
            <div class="container" id="homepage">
                <h1><b>Search Flights</b></h1>
                <br />
                <div>
                  <?php
                  $depart = '';
                  $query = "SELECT depart FROM vol GROUP BY depart ORDER BY depart ASC";
                  $result =pg_query($query);
                  while ($row=pg_fetch_array($result)):;    {
                    $depart .= '<option value="'.$row["depart"].'">'.$row["depart"].'</option>';
                  }endwhile;

                  ?>
                      <form method="post" id="insert_data">
                        <div class="row">
                            <div class="col-sm-6">
                              <select name="depart" id="depart" class="form-control action">
                                <option name="depart" value="">FROM</option>
                                  <?php echo $depart; ?>
                              </select>
                              <br />
                            </div>
                            <?php
                            $output = '';
                            if($_POST["action"] == 'depart'){
                              $query = "SELECT DISTINCT arrive FROM vol";
                              $result =pg_query($query);
                              while ($row=pg_fetch_array($result)):;    {
                                $output .= '<option value="'.$row["arrive"].'">'.$row["arrive"].'</option>';
                              }endwhile;
                              echo "<script>console.log('$output')</script>";
                            }

                             ?>
                            <div class="col-sm-6">
                              <select name="arrive" id="arrive" class="form-control action">
                                <option name="arrive" value="<<?php echo $output ?>" >TO</option>

                              </select>
                            </div>
                        </div>
                        <hr>
                        <div class="row">
                            <div class="col-sm-6">
                                <label for="depart">Depart:</label>
                                <input type="Date" class="form-control"  name="date_depart" required>
                            </div>
                        </div>
                        <div class="row">
                            <div class="col-sm-6">
                                <label for="class">Class:</label>
                                <select class="form-control" name="class_avion">
                                    <option value="Economy">Economy</option>
                                    <option value="Business">Business</option>
                                </select>
                            </div>
                        </div>
                        <br>
                        <div class="btn-group btn-group-justified">
                            <div class="btn-group">
                                <button type="submit" name="validate" class="btn btn-dark">Submit</button>
                            </div>
                            <div class="btn-group">
                                <button type="reset" class="btn btn-light" value="Reset">Reset</button>
                            </div>
                        </div>
                    </form>
                </div>
            </div>
        </div>
    </div>
<!-- partie JQuery pour les associations entre les deux select  -->
    <script>
    $(document).ready(function(){
    	$('.action').change(function(){
    		if($(this).val() != ''){
    			var action = $(this).attr("id");
    			var query = $(this).val();
    			var result = '';
    			if(action == 'depart')
    			{
    				result = 'arrive';
    			}
    			$.ajax({
    				url:'api.php',
    				method:"POST",
    				data:{action:action, query:query},
    				success:function(data){

    					$('#'+result).html(data);
              console.log("fin")
    				}
    			})
    		}
    	});
    });
    </script>

    <!-- END Reserve Section  -->

    <!-- Start Departures Section  -->
    <!-- Table d'affichages des vols  -->
    <!-- on recupere les donnees et on les affiches sous forme d'un tableau  -->
    <div id="feature" class="offset">
        <!-- Start Jumbotron -->
        <div class="jumbotron">
            <div class="narrow text-center">
                <h2>Departures</h2>
                <table class="table table-dark table-hover">
                    <thead>
                        <tr>
                            <th>Depart</th>
                            <th>Destination</th>
                            <th>Horaire Depart</th>
                            <th>Horaire Arrivee</th>
                            <th>Information</th>
                            <th>Place Disponible</th>

                        </tr>
                    </thead>
                    <tbody>
                      <?php foreach($emps as $key => $emp) :?>
                      <tr>
                        <form action="index.php" method="post">
                          <td><?php echo $emp['depart'] ?></td>
                          <td><?php echo $emp['arrive'] ?></td>
                          <td><?php echo $emp['horaire_depart'] ?></td>
                          <td><?php echo $emp['horaire_arrive'] ?></td>
                          <td><?php if ($emp['annulation']=='t') {
                            echo "<span class='ann'>ANNULE</span>";
                          }else {
                            echo "<span class='in-time'>IN TIME</span>";
                          }
                           ?></td>
                           <td><?php echo $emp["place_dispo"] ?></td>

                          </form>
                      </tr>

              <?php endforeach;?>

                    </tbody>
                </table>
            </div>
        </div>
        <!-- End Narrow-->
    </div>
    <!-- END jumbotron -->
    </div>

    <!-- END Departures Section  -->

    <!-- Start Footer Section -->
    <footer>
        <div class="footer-top">
            <div class="container">
                <div class="row">
                    <div class="col-md-3 col-sm-6 col-xs-12 segment-one md-mb-30 sm-mb-30">
                        <h3>OurAirport</h3>
                        <p>Reservez vos billets dès maintenant sur OurAirport</p>
                    </div>
                    <div class="col-md-3 col-sm-6 col-xs-12 segment-two md-mb-30 sm-mb-30">
                        <h2>Useful Link</h2>
                        <ul>
                            <li><a href="#">Home</a></li>
                            <li><a href="#">Reservation</a></li>
                            <li><a href="#">login</a></li>
                            <li><a href="#">about</a></li>
                        </ul>
                    </div>
                    <div class="col-md-3 col-sm-6 col-xs-12 segment-three sm-mb-30">
                        <h2>Follow us </h2>
                        <p>Please Follow us on our Social Media in order to keep updated</p>
                        <a href="#"><i class="fa fa-facebook"></i></a>
                        <a href="#"><i class="fa fa-twitter"></i></a>
                        <a href="#"><i class="fa fa-linkedin"></i></a>
                        <a href="#"><i class="fa fa-github"></i></a>
                    </div>
                    <div class="col-md-3 col-sm-6 col-xs-12 segment-four sm-mb-30">
                        <h2>Sign IN</h2>
                        <p>Join Our Team OurAirport</p>
                        <form action="">
                            <input type="submit" value="Create An Account">
                        </form>
                        <p><a href="logout.php">Deconnecté</a></p>
                    </div>
                </div>
            </div>
        </div>
        <p class="footer-bottom-text">All Right reserved by &copy;FoodLocation.2019</p>
    </footer>

</body>

</html>
