-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Sep 10, 2024 at 09:20 AM
-- Server version: 10.4.32-MariaDB
-- PHP Version: 8.0.30

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `eng_deu_vocab`
--

-- --------------------------------------------------------

--
-- Table structure for table `vocabulary`
--

DROP TABLE IF EXISTS `vocabulary`;
CREATE TABLE `vocabulary` (
  `id` int(100) NOT NULL,
  `English` varchar(255) NOT NULL,
  `Deutsch` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `vocabulary`
--

INSERT INTO `vocabulary` (`id`, `English`, `Deutsch`) VALUES
(1, 'airport', 'der Flughafen'),
(2, 'why', 'warum'),
(3, 'noon', 'Mittag'),
(4, 'difficult', 'schwierig'),
(5, 'fruit', 'das Obst'),
(6, 'answer', 'die Antwort'),
(7, 'other', 'andere'),
(8, 'to travel', 'reisen'),
(9, 'to read', 'lesen'),
(10, 'funny', 'lustig'),
(11, 'assignment', 'die Aufgabe'),
(12, 'Earth', 'die Erde'),
(13, 'any', 'jeder'),
(14, 'condition', 'der Zustand'),
(15, 'solution', 'die L^sung'),
(16, 'profession', 'der Beruf'),
(17, 'place', 'der Ort'),
(18, 'money', 'das Geld'),
(19, 'beginning', 'der Anfang'),
(20, 'yellow', 'gelb'),
(21, 'to get', 'erhalten'),
(22, 'to take', 'nehmen'),
(23, 'train', 'der Zug'),
(24, 'short', 'kurz'),
(25, 'airplane', 'das Flugzeug'),
(26, 'simple', 'einfach'),
(27, 'the same', 'gleich'),
(28, 'call', 'der Anruf'),
(29, 'to be called', 'hei`en'),
(30, 'tired', 'm_de'),
(31, 'sad', 'traurig'),
(32, 'finally', 'endlich'),
(33, 'quietly', 'ruhig'),
(34, 'to give', 'geben'),
(35, 'maybe', 'vielleicht'),
(36, 'cheap', 'billig'),
(37, 'expensive', 'teuer'),
(38, 'window', 'das Fenster'),
(39, 'still', 'noch'),
(40, 'always', 'immer'),
(41, 'where from', 'woher'),
(42, 'key', 'der Schl_ssel'),
(43, 'when', 'wann'),
(44, 'who', 'wer'),
(45, 'a lot', 'viel'),
(46, 'exam', 'die Pr_fung'),
(47, 'right now', 'gerade'),
(48, 'outside', 'drau`en'),
(49, 'to know', 'kennen'),
(50, 'people', 'die Leute'),
(51, 'bed', 'das Bett'),
(52, 'inside', 'drinnen'),
(53, 'refrigderator', 'der K_hlschrank'),
(54, 'empty', 'leer'),
(55, 'stairway', 'die Treppe'),
(56, 'elevator', 'der Aufzug');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `vocabulary`
--
ALTER TABLE `vocabulary`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `vocabulary`
--
ALTER TABLE `vocabulary`
  MODIFY `id` int(100) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=57;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
