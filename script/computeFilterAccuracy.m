function [neg, pos, zer] = computeFilterAccuracy (originalfile, filteredimage)

% Inputs:
%   originalfile is the original file as 512 x 512 bmp
%   filteredimage is the filtered image (where edges are black and the
% background is white) 
% Outputs: 
%  neg: false negatives
%  pos: false positives
%  zer: correctly detected edges
% Description: 
% This function compares the accuracy of an edge filtered image vs the
% matlab canny fiter implementation



filebinary = imread(filteredimage);
figure
imshow(filebinary)
originalfilebinary = imread(originalfile);
figure; title('originalfile')
imshow(originalfile)




%% if the edge filtered file is in gray scale
 idmax = (filebinary >= 35);
 idmin = (filebinary< 35);

 filebinaryflipped = zeros(size(filebinary));
 filebinaryflipped(idmin) = 0;
 filebinaryflipped(idmax) = 1;
 figure; title('edge filtered image flipped')
 imshow(filebinaryflipped);





%% Calculate the False positives and False negatives

 cannyfilter = edge(originalfilebinary, 'canny');
 cannyfilter = ~cannyfilter; 
 figure; title('canny filter')
 imshow(cannyfilter)
 
 
 size(cannyfilter)
 error  = cannyfilter - filebinaryflipped;



ind_pos = find(error == -1);
ind_neg = find(error == 1);
ind_zer = find(error == 0);



neg = length(ind_neg)/(512*512);
pos = length(ind_pos)/(512*512);
zer = length(ind_zer)/(512*512);


