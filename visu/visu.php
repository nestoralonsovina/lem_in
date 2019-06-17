<!DOCTYPE html>
<html>
<head>
<link href="style.css" rel="stylesheet" />
<meta charset=utf-8 />
<meta name="viewport" content="user-scalable=no, initial-scale=1.0, minimum-scale=1.0, maximum-scale=1.0, minimal-ui">
<title>Lem-in</title>
<script src="js/cytoscape.min.js"></script>
</head>
<body>
<?php
include 'parse.php';
$var = get_file();
$pos = json_encode(parse_dic($var));
$target = json_encode(target($var));
?>
<div id="cy"></div>
<script>
function get_parse(nb)
{
		var x_y = <?php echo $pos?>,
			tar = <?php echo $target?>;
		if (nb == 0)
			return (x_y);
		else if (nb == 1)
			return (tar);
		return (null);	
}
</script>
<script src="code.js"></script>
</body>
</html>
