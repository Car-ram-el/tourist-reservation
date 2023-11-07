// process: deposit money    no. of lines    amount      spin machine        check if won        prices/loses        play again/no amount left

const prompt=require("prompt-sync")();

const rows=3,cols=3;
const values={ ballsss:14, tennis:11, xbox:9, ball:7}
// const values={ ballsss:14, tennis:11, xbox:11, ball:7, mario:6, nintendo:3, tt:1}

const deposit=()=>{
    let num;
    while(true){
        num=prompt("Enter the deposit amount. \$"); num=Number.parseFloat(num);
        if(isNaN(num) || num<=0) console.log("Try again.");
        else break;
    }
    
    return num;
}

const lines=()=>{
    let num;
    while(true){
        num=prompt("How many lines from 1 to 3? "); num=Number.parseInt(num);
        if(num>0 && num<4) break; else console.log(`Come on.`);
    }
    return num;
}

const getBet=(balance,l)=>{
    let num;
    while(true){
        num=prompt("Your betting amount on a line please! "); num=Number.parseFloat(num);
        if(num>0 && num<=balance/l) break; else console.log("You don't have this much."); 
    }
    console.log(`\n\n\nA R C A D E * * * * * * *\n\n\n* * * * * * M A C H I N E\n\n\n`);
    return num;
}

const spin=()=>{
    // list of icons in vector
    const symbols=[];
    for (const [symbol,count] of Object.entries(values)) {
        if(count==14) symbols.push(symbol);
        else if(count==11) symbols.push(symbol,symbol);
        else if(count==9) symbols.push(symbol,symbol,symbol,symbol);
        else for(let i=0; i<8; ++i) symbols.push(symbol);
    }
    // reels for each column
    const reels=[];
    for(let j=0; j<cols; ++j){
        reels.push([]);
        const temp=[...symbols]; // copy to use for every reel
        for(let i=0; i<rows; ++i){
            let choose=Math.floor(Math.random()*temp.length);
            reels[j].push(temp[choose]);
            temp.splice(choose,1);
        }
    }
    // transpose to check wins
    const transpose=[];
    for(let i=0; i<rows; ++i){
        transpose.push([]);
        for(let j=0; j<cols; ++j){
            transpose[i].push(reels[j][i]);
        }
    }
    // print good view on console
    const machine=[];
    for(const row of transpose){
        let str=""; let t=[];
        for(let i=0; i<row.length; ++i){
            t.push(row[i]);
            let s=str.length;
            str+=row[i];
            for(let j=str.length; j<s+9; ++j) str+=" ";
            if(i!=row.length-1) str+=" | ";
        }
        console.log(str,`\n`); // good for console view
        machine.push(t);
    }
    return machine; // good for me to work on
}

const winning=(line,bet,machine)=>{
    let flag; let win=0;
    for(let i=0; i<line; ++i){ 
        flag=machine[i].every(e=>e===machine[i][0])?true:false; 
        if(flag) win+=bet*values[machine[i][0]];
    }
    console.log(`Your winning credits- \$${win}`);
    return win;
}

const game=()=>{
    let balance=deposit();
    while(true){
        const line=lines();
        const bet=getBet(balance,line); balance-=bet*line;
        const machine=spin();
        const win=winning(line,bet,machine); balance+=win;
        console.log(`You have \$${balance} right now.`);
        if(!balance){ console.log(`Insufficient balance\nG A M E\tO V E R`); break;}
        const again=prompt(`Play again or Exit (p/e)? `);
        if(again==`e`){ console.log(`Have a great day!`); break;}
    }
}
game();