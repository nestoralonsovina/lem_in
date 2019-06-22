#!/usr/bin/env php
<?php

function parse() {

	$file_graph = "graph_data.js";
	$file_turns = "turns_data.js";
	$graph_contents = "";
	$turns_contents = "";
	$graph_rooms = array();
	$graph_links = array();
	$turns_array = array();
	$type = 0;

	$is_comment = function ($l) {
		return $l[0] == '#' and $l !== "##start" and $l !== "##end";
	};

	$is_room = function ($l) {
		$room = explode(' ', $l);
		return sizeof($room) == 3 and strchr($l, '-') == false and $l[0] != 'L';
	};

	$is_link = function($l) {
		$link = explode('-', $l);
		return sizeof($link) == 2 and $l[0] != 'L';
	};

	$is_turns = function ($l) {
		return $l[0] == 'L';
	};

	$stdin = fopen('php://stdin', 'r');

	while ($line = fgets($stdin)) {
		$line = trim($line);

		#in this case we haven't even read the ants
		if ($graph_contents == "") {
			$graph_contents .= "var sourceCapacity = $line;";
			continue ;
		}

		# skip comments
		if ($is_comment($line) == true) {
			continue ;
		}

		# save links
		if ($is_link($line) == true) {
			$link = explode('-', $line);
			if (in_array(["source" => $link[1], "target" => $link[0]], $graph_links) == false) {
				array_push($graph_links, ["source" => $link[0], "target" => $link[1]]);
			}
			continue ;
		}

		#save turns
		if ($is_turns($line) == true) {
			$moves = explode(' ', $line);
			$move_arr = array();
			foreach ($moves as $move) {
				$info_move = explode('-', $move);
				$ant = substr($info_move[0], 1);
				array_push($move_arr, ["source" => $info_move[1], "target" => $info_move[2], "num" => (int)$ant]);
			}
			array_push($turns_array, $move_arr);
			continue ;
		}

		# if room save as room to graph_rooms
		if ($is_room($line) == true) {
			$room = explode(' ', $line);
			array_push($graph_rooms, ["name" => $room[0], "type" => $type]);
		}

		# this will always be reseted to 0, except that's why it's at the end
		if ($line == "##start") {
			$type = 1;
		} else if ($line == "##end") {
			$type = 2;
		} else {
			$type = 0;
		}
	}

	fclose($stdin);

	$graph_contents .= "var nodes_data = " . json_encode($graph_rooms) . ";";
	$graph_contents .= "var links_data = " . json_encode($graph_links) . ";";
	file_put_contents("visu/data/$file_graph", $graph_contents);
	$turns_contents .= "var turns_data = " . json_encode($turns_array) . ";";
	file_put_contents("visu/data/$file_turns", $turns_contents);
}

parse();
#exec("open visu/index.html");
