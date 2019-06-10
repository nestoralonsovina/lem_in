<?php 

function get_file()
{
	$file = file_get_contents('./maps', true);

	$var = explode("\n", $file);
	foreach ($var as $i => $k)
	{
		if ($var[$i] == "")
			break ;
		if ($var[$i] !== "##start" && $var[$i] !== "##end" )
			$arr[] = $k;
	}
	return ($arr);
}

function parse_dic($var)
{
	foreach ($var as $k)
	{
		$src = explode(" ", $k);
		if (count($src) == 3)
			$arr[] = array("label" => $src[0], "x" => $src[1], "y" => $src[2]);
	}
	return ($arr);
}

function target($var)
{
	foreach ($var as $k)
	{
		$src = explode("-", $k);
		if (count($src) == 2)
			$arr[] = array("source" => $src[0], "target" => $src[1]);
	}
	return ($arr);
}

?>
