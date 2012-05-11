# docs
WHITEPAPER	= whitepaper
MANUAL		= manual
TUTORIAL	= tutorial
PRESENTATION	= presentation
REPORT		= report

# call make recursively to build all docs
all:	
	# whitepaper
	$(MAKE) -C $(WHITEPAPER) TARGET=$(WHITEPAPER).pdf
	mv $(WHITEPAPER)/$(WHITEPAPER).pdf ./$(WHITEPAPER).pdf
	# reference manual
	$(MAKE) -C $(MANUAL) TARGET=$(MANUAL).pdf
	mv $(MANUAL)/$(MANUAL).pdf ./$(MANUAL).pdf
	# tutorial
	$(MAKE) -C $(TUTORIAL) TARGET=$(TUTORIAL).pdf
	mv $(TUTORIAL)/$(TUTORIAL).pdf ./$(TUTORIAL).pdf
	# presentation 
	$(MAKE) -C $(PRESENTATION) TARGET=$(PRESENTATION).pdf
	mv $(PRESENTATION)/$(PRESENTATION).pdf ./$(PRESENTATION).pdf
	# report
	$(MAKE) -C $(REPORT) TARGET=$(REPORT).pdf
	mv $(REPORT)/$(REPORT).pdf ./$(REPORT).pdf

# call make recursively to clean all docs
clean:	
	# whitepaper
	$(MAKE) -C $(WHITEPAPER) clean
	#rm -f $(WHITEPAPER).pdf
	# reference manual
	$(MAKE) -C $(MANUAL) clean
	#rm -f $(MANUAL).pdf
	# tutorial
	$(MAKE) -C $(TUTORIAL) clean
	#rm -f $(TUTORIAL).pdf
	# presentation
	$(MAKE) -C $(PRESENTATION) clean
	#rm -f $(PRESENTATION).pdf
	# report
	$(MAKE) -C $(REPORT) clean
	#rm -f $(REPORT).pdf
