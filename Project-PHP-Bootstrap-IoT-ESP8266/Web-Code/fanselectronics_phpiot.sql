-- phpMyAdmin SQL Dump
-- version 5.0.4
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jan 20, 2021 at 02:55 PM
-- Server version: 10.4.17-MariaDB
-- PHP Version: 7.4.13

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `fanselectronics_phpiot`
--

-- --------------------------------------------------------

--
-- Table structure for table `relay`
--

CREATE TABLE `relay` (
  `relay_id` int(11) NOT NULL,
  `nama_relay` varchar(64) NOT NULL,
  `logika` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `relay`
--

INSERT INTO `relay` (`relay_id`, `nama_relay`, `logika`) VALUES
(1, 'Kamar 1', 0),
(2, 'Kamar Mandi', 0),
(3, 'Kamar Tamu', 0),
(4, 'Ruang Makan', 0);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `relay`
--
ALTER TABLE `relay`
  ADD PRIMARY KEY (`relay_id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `relay`
--
ALTER TABLE `relay`
  MODIFY `relay_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
