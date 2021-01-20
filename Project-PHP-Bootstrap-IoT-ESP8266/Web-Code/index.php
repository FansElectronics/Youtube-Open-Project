<?php
include 'config.php';
$relay = $conn->query("SELECT * FROM relay");

if (isset($_GET['tombol'])) {
    $relay_id = $_GET['tombol'];
    $cek_id = $conn->query("SELECT * FROM relay WHERE relay_id = '$relay_id'");
    if ($cek_id->num_rows > 0) {
        $rly = $cek_id->fetch_assoc();
        if ($rly['logika'] == 1) {
            $logika = 0;
        } else {
            $logika = 1;
        }
        $conn->query("UPDATE relay SET logika = '$logika' WHERE relay_id = '$relay_id'");
    }
    header("location: index.php");
}
?>

<!doctype html>
<html lang="en">

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">

    <title>Project PHP Bootstrap IoT ESP8266 - Fans Electronics</title>
</head>

<body>
    <div class="container">
        <div class="card bg-light">
            <div class="card-header">Project PHP Bootstrap IoT ESP8266 - Fans Electronics</div>
            <div class="card-body">
                <?php while ($row = $relay->fetch_assoc()) { ?>
                    <?php if ($row['logika'] == 1) { ?>
                        <?php $logika = 'ON'; ?>
                    <?php } else { ?>
                        <?php $logika = 'OFF'; ?>
                    <?php } ?>
                    <div class='row'>
                        <a href="<?= $url; ?>/index.php?tombol=<?= $row['relay_id'] ?>" class="btn btn-dark btn-block btn-success"> <?= $row['nama_relay'] ?> = <?= $logika ?></a>
                    </div>
                    <br>
                <?php } ?>
            </div>
        </div>
    </div>


    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
</body>

</html>