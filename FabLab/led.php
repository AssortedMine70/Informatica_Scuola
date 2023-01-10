<!DOCTYPE HTML>
<html>
<head>
	<title>Led</title>
	<style>
	div.led {
		width: 150px;
		height: 150px;
		border-radius: 75px;
		background-color: #00AA66;
	}
	div.led.red {
		background-color: #D80000;
	}  
	</style>
</head>
<body>
	<?php
	print_r($_POST);
	$s = shell_exec("gpio read 0");
	if(isset($_POST["toggle"])) {
		echo $s;
		//passthru("gpio read 0");
		passthru("gpio toggle 0");
		$s = shell_exec("gpio read 0");
		echo $s;	
		//passthru("gpio read 0");
	}
	?>
	<form  method="POST">
	<input type="submit" name="toggle" value=<?=($s==0?"ON":"OFF")?>>
	</form>
	<div class="led<?=($s==0?" red":"")?>"></div>
</body>
</html>
