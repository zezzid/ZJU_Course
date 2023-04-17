%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                       Anti-smearing function                     %
%       code by Fabrizio Conso, university of pavia, student       %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                  %
 function fout = antismear(fin,fs,nfft)
 % fin  = normalized signal frequency
 % fs   = normalized sampling frequency
 % nfft = number of fft points
 format long;
 ts=1/fs;
 c=primes(nfft*ts*fin);
 maxprimes=max(c);
 fout=maxprimes/(nfft*ts);
%                                                                  %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%