library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity xpress_uart is
	port(
		nRESET_in	    : in std_logic;
		CLK_in		    : in std_logic;
		
		CLK_PRESCALER_in : in std_logic_vector(15 downto 0);
		
		UART_STATUS_out : out std_logic_vector(15 downto 0);
		
		TX_DATA_in	    : in std_logic_vector (7 downto 0);
		LD_TX_in	    : in std_logic;
		
		RX_DATA_out		: out std_logic_vector(7 downto 0);
		CLR_RX_DATA_in	: in std_logic;
		
		RXD_in			: in std_logic;
		TXD_out			: out std_logic
		
		);
end entity;
		
architecture rtl of xpress_uart is

	signal tx_bit: integer range 9 downto 0;
	signal tx_data: std_logic_vector (9 downto 0);
	signal tx_prescaler:  std_logic_vector(15 downto 0);
	signal tx_busy : std_logic;
	
	signal rx_bit,next_rx_bit				: integer range 9 downto 0;
	signal rx_data,next_rx_data				: std_logic_vector (9 downto 0);
	signal rx_prescaler	,next_rx_prescaler	: std_logic_vector(15 downto 0);
	signal rx_ready		,next_rx_ready		: std_logic;
	signal rx_overrun	,next_rx_overrun	: std_logic;
	signal rx0,rx1							: std_logic;
	signal rx_data_out_s, next_rx_data_out	: std_logic_vector (7 downto 0);
	
	
	-- Build an enumerated type for the state machine
	type state_type is (WAITING_START,WAITING_BITS);
	
	-- Register to hold the current state
	signal rx_state, next_rx_state : state_type;
	
begin

	rx_data_out <= rx_data_out_s;
	TXD_out <= tx_data(9);

	process (tx_busy,rx_ready)
	begin
		UART_STATUS_out <= (others=>'0');
		UART_STATUS_out(0) <= tx_busy;
		UART_STATUS_out(1) <= rx_ready;
		UART_STATUS_out(2) <= rx_overrun;
	end process;
	
	-- Transmitter 
	tx_busy <= '1' when tx_bit<9 else '0';

	process (nRESET_in, CLK_in, CLK_PRESCALER_in)
	begin 	
		if nRESET_in='0' then
			tx_data <= (others=>'1');
			tx_bit <= 9;
			tx_prescaler <= (others=>'0');
		elsif rising_edge(CLK_in) then
		
		
			if LD_TX_in='1' then
				tx_data <= "0" & TX_DATA_in & "1"; -- start + data + stop
				tx_bit <= 0;
				tx_prescaler <= CLK_PRESCALER_in;
			else
				if tx_prescaler="0000000000000000" and tx_bit<9 then
					tx_prescaler <= CLK_PRESCALER_in;
					tx_data <= tx_data(8 downto 0) & "1";
					tx_bit <= tx_bit+1;
				else 
					tx_prescaler <= std_logic_vector(unsigned(tx_prescaler) - 1);
				end if;
				
			end if;

		end if;

	end process;
	
	-- Receiver
	
	process (nRESET_in, CLK_in, next_rx_state,next_rx_bit,next_rx_overrun,next_rx_ready,next_rx_prescaler,next_rx_data_out)
	begin
		if nRESET_in = '0' then
			rx_bit <= 0;
			rx_data <= (others=>'0');
			rx_state <= WAITING_START;
			rx_ready <= '0';
			rx_overrun <= '0';
			rx_prescaler <= (others=>'0'); 
			rx_data_out_s <= (others=>'0');
			rx0 <= '1';
			rx1 <= '1';
		elsif rising_edge(CLK_in) then
			rx0 <= rx1;
			rx1 <= RXD_in;
			rx_data <= next_rx_data;
			rx_state <= next_rx_state;
			rx_bit <= next_rx_bit;
			rx_ready <= next_rx_ready;
			rx_overrun <= next_rx_overrun;
			rx_prescaler <= next_rx_prescaler;
			rx_data_out_s <= next_rx_data_out;
		end if;	
	end process;
	
	process (rx1,rx0,rx_state,CLR_RX_DATA_in,rx_bit,rx_ready,rx_overrun,rx_prescaler,rx_data,rx_data_out_s)
	begin
	
		next_rx_state <= rx_state;
		next_rx_bit <= rx_bit;
		next_rx_ready <= rx_ready;
		next_rx_overrun <= rx_overrun;
		next_rx_prescaler <= std_logic_vector(unsigned(rx_prescaler)-1);
		next_rx_data <= rx_data;
		next_rx_data_out <= rx_data_out_s;
		
		case rx_state is
		
			when WAITING_START =>if rx0='1' and rx1='0' then
									next_rx_prescaler <= "0" & CLK_PRESCALER_in(15 downto 1);
									next_rx_state <= WAITING_BITS;
									next_rx_bit <= 0;
								end if;
		
								
			
			when WAITING_BITS =>	if unsigned(rx_prescaler)=0 then
										next_rx_data <= rx_data(8 downto 0) & rx0;
										next_rx_prescaler <= CLK_PRESCALER_in; 	
										if rx_bit = 9 then 
											next_rx_state <= WAITING_START;
											next_rx_data_out <= rx_data(7 downto 0);
											if rx_ready='1' then
												next_rx_overrun<='1';
											end if;
											next_rx_ready <= '1';
												
										else
											next_rx_bit <= rx_bit +1;
										end if;
					
									end if;
									
		end case;
		
		if CLR_RX_DATA_in='1' then
			next_rx_ready <= '0';
			next_rx_overrun <='0';
		end if;
																			
	end process;
	
	
end architecture;