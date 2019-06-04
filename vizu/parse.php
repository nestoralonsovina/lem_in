#!/usr/bin/php

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
	function parse_dic()
	{
		$arr = get_file();
		$i = 1;
		
	}
	$arr = parse_dic();
?>
