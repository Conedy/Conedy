test:
	find ./ -mindepth 1 -maxdepth 1 -path '*/.svn' -prune  -o  -type d -exec sh -c "echo {} && make -s  -C {} test" \;


clean:
	find ./ -mindepth 1 -maxdepth 1 -path '*/.svn' -prune  -o  -type d -exec sh -c "echo {} && make -s  -C {} clean" \;




submit:
	find ./ -mindepth 1 -maxdepth 1 -path '*/.svn' -prune  -o  -type d -exec sh -c "echo {} && make -s  -C {} submit" \;

