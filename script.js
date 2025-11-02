// Simulated C program functionality
class SportsLeaderboard {
    constructor() {
        this.players = [];
        this.running = true;
        this.loadSampleData();
    }

    loadSampleData() {
        this.players = [
            { name: "Michael Johnson", country: "USA", score: 95 },
            { name: "Sarah Williams", country: "UK", score: 87 },
            { name: "Carlos Rodriguez", country: "Spain", score: 92 },
            { name: "Yuki Tanaka", country: "Japan", score: 78 },
            { name: "Anna Schmidt", country: "Germany", score: 88 }
        ];
        this.mergeSort(0, this.players.length - 1);
    }

    // Merge Sort Implementation
    mergeSort(left, right) {
        if (left < right) {
            const mid = Math.floor((left + right) / 2);
            this.mergeSort(left, mid);
            this.mergeSort(mid + 1, right);
            this.merge(left, mid, right);
        }
    }

    merge(left, mid, right) {
        const leftArr = this.players.slice(left, mid + 1);
        const rightArr = this.players.slice(mid + 1, right + 1);
        
        let i = 0, j = 0, k = left;
        
        while (i < leftArr.length && j < rightArr.length) {
            if (leftArr[i].score >= rightArr[j].score) {
                this.players[k] = leftArr[i];
                i++;
            } else {
                this.players[k] = rightArr[j];
                j++;
            }
            k++;
        }
        
        while (i < leftArr.length) {
            this.players[k] = leftArr[i];
            i++;
            k++;
        }
        
        while (j < rightArr.length) {
            this.players[k] = rightArr[j];
            j++;
            k++;
        }
    }

    displayLeaderboard() {
        let output = "================ LEADERBOARD ===============\n";
        output += "Rank  Name                      Country         Score\n";
        output += "---------------------------------------------\n";
        
        this.players.forEach((player, index) => {
            let medal = "   ";
            if (index === 0) medal = " 🥇";
            else if (index === 1) medal = " 🥈";
            else if (index === 2) medal = " 🥉";
            
            output += `${(index + 1).toString().padStart(2)}${medal} ${player.name.padEnd(24)} ${player.country.padEnd(14)} ${player.score}\n`;
        });
        
        output += "=============================================\n";
        output += "\nSorting Algorithm: Merge Sort\n";
        output += "Time Complexity: O(n log n)\n";
        output += "Space Complexity: O(n)\n";
        
        return output;
    }

    addPlayer(name, country, score) {
        const newPlayer = { name, country, score: parseInt(score) };
        this.players.push(newPlayer);
        this.mergeSort(0, this.players.length - 1);
        return `Player '${name}' added successfully!\n`;
    }

    generateSampleData() {
        const samplePlayers = [
            { name: "David Smith", country: "Australia", score: 79 },
            { name: "Maria Garcia", country: "Mexico", score: 91 },
            { name: "Luca Bianchi", country: "Italy", score: 83 },
            { name: "Pierre Dubois", country: "France", score: 90 },
            { name: "Emma Chen", country: "Canada", score: 85 }
        ];
        
        this.players.push(...samplePlayers);
        this.mergeSort(0, this.players.length - 1);
        return "Sample data generated successfully! Added 5 new players.\n";
    }
}

// Initialize the leaderboard
const leaderboard = new SportsLeaderboard();

// Function to execute actions
function executeAction(choice) {
    const output = document.getElementById('terminal-content');
    
    switch(choice) {
        case 1: // Add Player
            const name = prompt("Enter player name:");
            const country = prompt("Enter player country:");
            const score = prompt("Enter player score:");
            
            if (name && country && score) {
                const result = leaderboard.addPlayer(name, country, score);
                output.innerHTML = `<pre>${result}</pre>` + output.innerHTML;
            }
            break;
            
        case 2: // Sort Leaderboard
            leaderboard.mergeSort(0, leaderboard.players.length - 1);
            output.innerHTML = `<pre>Leaderboard sorted successfully using Merge Sort!\n</pre>` + output.innerHTML;
            break;
            
        case 3: // Display Leaderboard
            const leaderboardOutput = leaderboard.displayLeaderboard();
            output.innerHTML = `<pre class="leaderboard-output">${leaderboardOutput}</pre>` + output.innerHTML;
            break;
            
        case 4: // Generate Sample Data
            const sampleResult = leaderboard.generateSampleData();
            output.innerHTML = `<pre>${sampleResult}</pre>` + output.innerHTML;
            break;
            
        case 7: // Exit
            output.innerHTML = `<pre>Thank you for using the Sports Leaderboard System!\nProgram terminated.</pre>` + output.innerHTML;
            break;
            
        default:
            output.innerHTML = `<pre>Invalid choice! Please try again.</pre>` + output.innerHTML;
    }
    
    // Auto-scroll to top
    document.getElementById('output').scrollTop = 0;
}

// Initial display
document.addEventListener('DOMContentLoaded', function() {
    const initialOutput = leaderboard.displayLeaderboard();
    document.getElementById('terminal-content').innerHTML = 
        `<div class="welcome-message">
            <p>🚀 Sports Leaderboard System Started!</p>
            <p>Merge Sort Algorithm Ready</p>
            <br>
            <pre>${initialOutput}</pre>
        </div>`;
});
