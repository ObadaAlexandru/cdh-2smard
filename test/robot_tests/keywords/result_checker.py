def hello_world():
    print "Hello world"


def get_results_for(half, path):
    with open(str(path), "r") as resultFile:
        lines = resultFile.readlines()
        filter = lambda items, content: [item for item in items if content in item]
        half_lines = filter(lines, "half_" + half)
        print half_lines
        activations = len(filter(half_lines, "A"))
        deactivations = len(filter(half_lines, "I"))
        return activations, deactivations
