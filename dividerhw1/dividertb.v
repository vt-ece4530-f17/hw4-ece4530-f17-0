module dividertb;

   reg [15:0] N;
   reg [15:0] D;
   reg 	      start;
   reg 	      clk;
   reg 	      reset;

   wire [7:0]  Q;
   reg  [7:0]  Qexp;
   wire [15:0] R;
   reg  [15:0] Rexp;
   wire        done;

   divider mydiv(clk, reset, N, D, start, Q, R, done);
		 
   reg [55:0]  dvectors[7999:0];
   reg [13:0]  vnum;
   reg [31:0]  errors;
   
   initial
     begin
	$readmemh("divisor.tv", dvectors);
	vnum = 0;
	errors = 0;	
     end
   
   initial
     begin
	clk = 0;
	start = 0;
	reset = 1;
     end

   always #25 clk = ~clk;
   
   initial 
     begin
	repeat (5) @(posedge clk) ;
	reset = 0;
	
	repeat (8000)
	  begin
	     repeat (10) @(posedge clk) ;

	     {N, D, Qexp, Rexp} = dvectors[vnum];
	     start = 1;
	     @(posedge clk) ;
	     start = 0;
	      
	     @(posedge done) ;
	     $display("%4h %4h %2h %4h", N, D, Q, R);

	     if ((Qexp != Q) | (Rexp != R))
	       begin
		  $display("Error. %4h / %4h. Expected %2h %4h but found %2h %4h", N, D, Qexp, Rexp, Q, R);
		  errors = errors + 1;		  
	       end
	     vnum = vnum + 1;
	  end

	$display("Done. Found %d errors.", errors);	
	$finish;

     end
   
endmodule
