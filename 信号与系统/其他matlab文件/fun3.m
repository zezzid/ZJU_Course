function [f] = fun3(t)
f=1/pi.*arrayfun(@(t)integral(@(w) (sin(w./2)).^2./(w.*sin(w)).*cos(w.*t),-Inf,Inf),t);
end

