--
-- this is a test to see how good or bad does a mux datapath compiles into actel fpga fabric
--
-- >231 cells... for 16 x 12 mux

-- 12:1 mux
library ieee;
use ieee.std_logic_1164.all;
-- Entity declaration:
entity mux12_1 is
port
(
mux_sel: in std_logic_vector (3 downto 0);-- mux select
A: in std_logic_vector (15 downto 0);
B: in std_logic_vector (15 downto 0);
C: in std_logic_vector (15 downto 0);
D: in std_logic_vector (15 downto 0);
E: in std_logic_vector (15 downto 0);
F: in std_logic_vector (15 downto 0);
G: in std_logic_vector (15 downto 0);
H: in std_logic_vector (15 downto 0);
I: in std_logic_vector (15 downto 0);
J: in std_logic_vector (15 downto 0);
K: in std_logic_vector (15 downto 0);
M: in std_logic_vector (15 downto 0);
mux_out: out std_logic_vector (15 downto 0) -- mux output
);
end mux12_1;
-- Architectural body:
architecture synth of mux12_1 is
begin
proc1: process (mux_sel, A, B, C, D, E, F, G, H, I, J, K, M)
begin
case mux_sel is
when "0000" => mux_out<= A;
when "0001" => mux_out <= B;
when "0010" => mux_out <= C;
when "0011" => mux_out <= D;
when "0100" => mux_out <= E;
when "0101" => mux_out <= F;
when "0110" => mux_out <= G;
when "0111" => mux_out <= H;
when "1000" => mux_out <= I;
when "1001" => mux_out <= J;
when "1010" => mux_out <= K;
when "1011" => mux_out <= M;
when others => mux_out<= (others=>'0');
end case;
end process proc1;
end synth;